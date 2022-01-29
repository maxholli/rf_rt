// ======================================================================== //
// Copyright 2018-2019 Ingo Wald                                            //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include <optix_device.h>

#include "LaunchParams.h"

using namespace osc;

namespace osc {
  
  /*! launch parameters in constant memory, filled in by optix upon
      optixLaunch (this gets filled in from the buffer we pass to
      optixLaunch) */
  extern "C" __constant__ LaunchParams optixLaunchParams;

  // for this simple example, we have a single ray type
  enum { SURFACE_RAY_TYPE=0, RAY_TYPE_COUNT };
  
  static __forceinline__ __device__
  void *unpackPointer( uint32_t i0, uint32_t i1 )
  {
    const uint64_t uptr = static_cast<uint64_t>( i0 ) << 32 | i1;
    void*           ptr = reinterpret_cast<void*>( uptr ); 
    return ptr;
  }

  static __forceinline__ __device__
  void  packPointer( void* ptr01,
                      void* ptr23, 
                      void* ptr45, 
                      void* ptr67, 
                      uint32_t& i0, uint32_t& i1, 
                      uint32_t& i2, uint32_t& i3, 
                      uint32_t& i4, uint32_t& i5,
                      uint32_t& i6, uint32_t& i7)
  {
    const uint64_t uptr1 = reinterpret_cast<uint64_t>( ptr01 );
    i0 = uptr1 >> 32;
    i1 = uptr1 & 0x00000000ffffffff;
    
    const uint64_t uptr2 = reinterpret_cast<uint64_t>( ptr23 );
    i2 = uptr2 >> 32;
    i3 = uptr2 & 0x00000000ffffffff;

    const uint64_t uptr3 = reinterpret_cast<uint64_t>( ptr45 );
    i4 = uptr3 >> 32;
    i5 = uptr3 & 0x00000000ffffffff;

    const uint64_t uptr4 = reinterpret_cast<uint64_t>( ptr67 );
    i6 = uptr4 >> 32;
    i7 = uptr4 & 0x00000000ffffffff;
  }

  template<typename T>
  static __forceinline__ __device__ T *getPRD01()
  { 
    const uint32_t u0 = optixGetPayload_0();
    const uint32_t u1 = optixGetPayload_1();
    return reinterpret_cast<T*>( unpackPointer( u0, u1 ) );
  }

  template<typename T>
  static __forceinline__ __device__ T *getPRD23()
  { 
    const uint32_t u2 = optixGetPayload_2();
    const uint32_t u3 = optixGetPayload_3();
    return reinterpret_cast<T*>( unpackPointer( u2, u3 ) );
  }

  template<typename T>
  static __forceinline__ __device__ T *getPRD45()
  { 
    const uint32_t u4 = optixGetPayload_4();
    const uint32_t u5 = optixGetPayload_5();
    return reinterpret_cast<T*>( unpackPointer( u4, u5 ) );
  }

  template<typename T>
  static __forceinline__ __device__ T *getPRD67()
  { 
    const uint32_t u6 = optixGetPayload_6();
    const uint32_t u7 = optixGetPayload_7();
    return reinterpret_cast<T*>( unpackPointer( u6, u7 ) );
  }


  // for RANDOM THINGS =============================================
  template<unsigned int N>
  static __host__ __device__ __inline__ unsigned int tea( unsigned int val0, unsigned int val1 )
  {
    unsigned int v0 = val0;
    unsigned int v1 = val1;
    unsigned int s0 = 0;

    for( unsigned int n = 0; n < N; n++ )
    {
      s0 += 0x9e3779b9;
      v0 += ((v1<<4)+0xa341316c)^(v1+s0)^((v1>>5)+0xc8013ea4);
      v1 += ((v0<<4)+0xad90777d)^(v0+s0)^((v0>>5)+0x7e95761e);
    }

    return v0;
  }

  // Generate random unsigned int in [0, 2^24)
  static __host__ __device__ __inline__ unsigned int lcg(unsigned int &prev)
  {
    const unsigned int LCG_A = 1664525u;
    const unsigned int LCG_C = 1013904223u;
    prev = (LCG_A * prev + LCG_C);
    return prev & 0x00FFFFFF;
  }

    // Generate random float in [0, 1)
  static __host__ __device__ __inline__ float rnd(unsigned int &prev)
  {
    return ((float) lcg(prev) / (float) 0x01000000);
  }
  
  // generate random float in [min, max)
  static __host__ __device__ __inline__ float rnd(unsigned int &prev, float min, float max)
  {
    return min + (max-min)*rnd(prev);
  }

  static __host__ __device__ __inline__ float clamp(float x, float min, float max)
  {
    if (x < min) return min;
    if (x > max) return max;
    return x;
  }

  static __host__ __device__ __inline__ bool near_zero(vec3f v)
  {
    const float s = 1e-5;
    return (fabsf(v.x) < s) && (fabsf(v.y) < s) && (fabsf(v.z) < s);
  }

  static __host__ __device__ __inline__ float vec_length(vec3f v)
  {
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
  }

  static __host__ __device__ __inline__ vec3f unit_vector(vec3f v)
  {
    return v / vec_length(v);
  }

  static __host__ __device__ __inline__ vec3f reflect(vec3f v, vec3f n)
  {
    return v - 2*dot(v,n)*n;
  }


  //------------------------------------------------------------------------------
  // closest hit and anyhit programs for radiance-type rays.
  //
  // Note eventually we will have to create one pair of those for each
  // ray type and each geometry type we want to render; but this
  // simple example doesn't use any actual geometries yet, so we only
  // create a single, dummy, set of them (we do have to have at least
  // one group of them to set up the SBT)
  //------------------------------------------------------------------------------
  
  extern "C" __global__ void __closesthit__radiance()
  {
    const TriangleMeshSBTData &sbtData
      = *(const TriangleMeshSBTData*)optixGetSbtDataPointer();

    // compute normal:
    const int   primID = optixGetPrimitiveIndex();
    const vec3i index  = sbtData.index[primID];
    const vec3f &A     = sbtData.vertex[index.x];
    const vec3f &B     = sbtData.vertex[index.y];
    const vec3f &C     = sbtData.vertex[index.z];
    const vec3f Ng     = -1.0f * normalize(cross(B-A,C-A));
    // const vec3f Ng     = normalize(cross(B-A,C-A));

    // const vec3f hit_point = 
    const vec3f rayOrig = optixGetWorldRayOrigin();
    const vec3f rayDir = optixGetWorldRayDirection();

    const float D = -1.0f*Ng.x*A.x - Ng.y*A.y - Ng.z*A.z;

    const float denom = dot(rayDir, Ng);
    const float cosDN  = 0.2f + .8f*fabsf(denom);
    const float t = -1.0f * (dot(Ng, rayOrig) + D) / denom;

    // location of the hit 
    const vec3f p_hit = rayOrig + rayDir * t;
    vec3f &prd_hit_p = *(vec3f*)getPRD23<vec3f>();
    prd_hit_p = p_hit + (Ng * 0.001f);

    const vec3f material = sbtData.material;

    // find the direction of the bounced ray
    // eventually this needs to be based on the sbtdata, which will carry the surface type. 
    
    // relay surface type back to raygen, because I want to use the random seed i started there.
    // i don't know how to ensure I get a random number here within closest hit. 
    // I probably need to pass &prev along with the 
    vec3f &prd_new_ray_dir = *(vec3f*)getPRD45<vec3f>();
    if (material.x == 0.0) 
    {
      // ----------- Scatter --------------
      unsigned int &prd_seed = *(unsigned int*)getPRD67<unsigned int>();
      
      float rx = 0.0;
      float ry = 0.0;
      float rz = 0.0;
      while (true)
      {
        rx = rnd( prd_seed, -1.f, 1.f);
        ry = rnd( prd_seed, -1.f, 1.f);
        rz = rnd( prd_seed, -1.f, 1.f);
        if (sqrtf(rx*rx + ry*ry + rz*rz) >= 1) continue;
        break;
      }
      // const vec3f new_ray_dir = normalize(vec3f(rx, ry, rz) + Ng);
      vec3f scatter_direction = vec3f(rx, ry, rz) + Ng;
      if (near_zero(scatter_direction))
        scatter_direction = Ng;
      prd_new_ray_dir = scatter_direction;
      // -----------------------------------
    } 
    else if (material.x == 1.0)
    {
      // ------------- Reflection ----------
      vec3f reflected = reflect(unit_vector(rayDir), Ng);
      prd_new_ray_dir = reflected;
      // -----------------------------------
    } 
    else if (material.x == 2.0)
    {
      //------------- Fuzzed --------------
      vec3f reflected = reflect(unit_vector(rayDir), Ng);
      float fuzz = material.y;
      unsigned int &prd_seed = *(unsigned int*)getPRD67<unsigned int>();
      
      float rx = 0.0;
      float ry = 0.0;
      float rz = 0.0;
      while (true)
      {
        rx = rnd( prd_seed, -1.f, 1.f);
        ry = rnd( prd_seed, -1.f, 1.f);
        rz = rnd( prd_seed, -1.f, 1.f);
        if (sqrtf(rx*rx + ry*ry + rz*rz) >= 1) continue;
        break;
      }
      vec3f fuzzed = reflected + (vec3f(rx, ry, rz) * fuzz);
      if (near_zero(fuzzed))
        fuzzed = reflected; 
      prd_new_ray_dir = fuzzed;
      //-----------------------------------
    }
    else if (material.x == 3.0)
    {
      //------------- light source --------------
      prd_hit_p = vec3f(999999.99f,999999.99f,999999.99f);
      //-----------------------------------
    }

    vec3f &prd = *(vec3f*)getPRD01<vec3f>();
    // prd = sbtData.color;
    prd = cosDN * sbtData.color;
    
  }
  
  extern "C" __global__ void __anyhit__radiance()
  { /*! for this simple example, this will remain empty */ }


  
  //------------------------------------------------------------------------------
  // miss program that gets called for any ray that did not have a
  // valid intersection
  //
  // as with the anyhit/closest hit programs, in this example we only
  // need to have _some_ dummy function to set up a valid SBT
  // ------------------------------------------------------------------------------
  
  extern "C" __global__ void __miss__radiance()
  {
    vec3f &prd = *(vec3f*)getPRD01<vec3f>();
    vec3f &prd_hit_p = *(vec3f*)getPRD23<vec3f>();
    // fake value for hit point, so I know to end the ray bouncing
    prd_hit_p = vec3f(999999.99f,999999.99f,999999.99f);

    // rayDir should be normalized becasue that happens in raygen__renderFrame()
    const vec3f rayDir = optixGetWorldRayDirection();
    // const vec3f n_rayDir = normalize(rayDir);

    const float t = 0.5*(rayDir.y + 1.0);
    const float tin = 1.0 - t;
    //(1.0-t)*vec3f(1.f) +
    //sky that fades to white
    prd = tin*vec3f(1.f,1.f,1.f) + t*vec3f(0.5f,0.7f,1.0f);
    // sky that's solid light blue
    // prd = vec3f(0.5f,0.7f,1.0f);
    // background black
    // prd = vec3f(0.f);
  }

  //------------------------------------------------------------------------------
  // ray gen program - the actual rendering happens in here
  //------------------------------------------------------------------------------
  extern "C" __global__ void __raygen__renderFrame()
  {
    // compute a test pattern based on pixel ID
    const int ix = optixGetLaunchIndex().x;
    const int iy = optixGetLaunchIndex().y;
    const uint3 dim = optixGetLaunchDimensions();

    const auto &camera = optixLaunchParams.camera;
    const uint32_t fbIndex = ix+iy*optixLaunchParams.frame.size.x;

    unsigned int seed = tea<4>( iy * dim.x + ix, 12346789 + fbIndex );
    // our per-ray data for this example. what we initialize it to
    // won't matter, since this value will be overwritten by either
    // the miss or hit program, anyway
    vec3f rayColorPRD = vec3f(0.f);
    vec3f ray_hit_p = vec3f(0.f);
    vec3f ray_dir_new = vec3f(0.f);
    // the values we store the PRD pointer in:
    uint32_t u0, u1, u2, u3, u4, u5, u6, u7;
    packPointer( &rayColorPRD, &ray_hit_p, &ray_dir_new, &seed, u0, u1, u2, u3, u4, u5, u6, u7);

    // normalized screen plane position, in [0,1]^2
    vec2f screen = vec2f(0.f);
    
    const int samples_per_pixel = 20;

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    for (int s = 0; s < samples_per_pixel; s++)
    {
      float rx = rnd( seed );
      float ry = rnd( seed );

      screen = vec2f(rx+ix+.5f,ry+iy+.5f)
                       / vec2f(optixLaunchParams.frame.size);
      // screen = vec2f(ix+.5f,iy+.5f)
      //                  / vec2f(optixLaunchParams.frame.size);

      ray_dir_new = normalize(camera.direction
                             + (screen.x - 0.5f) * camera.horizontal
                             + (screen.y - 0.5f) * camera.vertical);
      
      ray_hit_p = camera.position;

      int max_ray_depth = 50;
      int bounces = 0;

      float temp_r = 1.0;
      float temp_g = 1.0;
      float temp_b = 1.0;

      while (bounces < max_ray_depth)
      {
      // // for (int depth=0; depth<max_ray_depth; depth++)
      // // {
        // int num_bounces = 0;
        optixTrace(optixLaunchParams.traversable,
                  ray_hit_p,
                  ray_dir_new,
                  0.f,    // tmin
                  1e20f,  // tmax
                  0.0f,   // rayTime
                  OptixVisibilityMask( 255 ),
                  OPTIX_RAY_FLAG_DISABLE_ANYHIT,//OPTIX_RAY_FLAG_NONE,
                  SURFACE_RAY_TYPE,             // SBT offset
                  RAY_TYPE_COUNT,               // SBT stride
                  SURFACE_RAY_TYPE,             // missSBTIndex 
                  u0, u1, u2, u3, u4, u5, u6, u7 );
        temp_r *= rayColorPRD.x;
        temp_g *= rayColorPRD.y;
        temp_b *= rayColorPRD.z;
        if (ray_hit_p.x == 999999.99f)
          break;
        bounces++;
      }
      if (bounces == max_ray_depth && max_ray_depth != 1) {
        temp_r *= 0;
        temp_g *= 0;
        temp_b *= 0;
      }
      r += temp_r;
      g += temp_g;
      b += temp_b;
    }
    // scale by the number of samples, then scale to 256
    const int r_out = int(clamp(sqrtf(r/samples_per_pixel), 0.0f, 0.999f) * 255.99f);
    const int g_out = int(clamp(sqrtf(g/samples_per_pixel), 0.0f, 0.999f) * 255.99f);
    const int b_out = int(clamp(sqrtf(b/samples_per_pixel), 0.0f, 0.999f) * 255.99f);

    // convert to 32-bit rgba value (we explicitly set alpha to 0xff
    // to make stb_image_write happy ...
    const uint32_t rgba = 0xff000000
      | (r_out<<0) | (g_out<<8) | (b_out<<16);

    // and write to frame buffer ...
    
    optixLaunchParams.frame.colorBuffer[fbIndex] = rgba;
  }
  
} // ::osc
