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
  void  packPointer( void* ptr, uint32_t& i0, uint32_t& i1 )
  {
    const uint64_t uptr = reinterpret_cast<uint64_t>( ptr );
    i0 = uptr >> 32;
    i1 = uptr & 0x00000000ffffffff;
  }

  template<typename T>
  static __forceinline__ __device__ T *getPRD()
  { 
    const uint32_t u0 = optixGetPayload_0();
    const uint32_t u1 = optixGetPayload_1();
    return reinterpret_cast<T*>( unpackPointer( u0, u1 ) );
  }


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
    const vec3f Ng     = normalize(cross(B-A,C-A));

    const vec3f rayDir = optixGetWorldRayDirection();
    const float cosDN  = 0.2f + .8f*fabsf(dot(rayDir,Ng));
    vec3f &prd = *(vec3f*)getPRD<vec3f>();
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
    vec3f &prd = *(vec3f*)getPRD<vec3f>();

    // rayDir should be normalized becasue that happens in raygen__renderFrame()
    const vec3f rayDir = optixGetWorldRayDirection();
    // const vec3f n_rayDir = normalize(rayDir);

    const float t = 0.5*(rayDir.y + 1.0);
    const float tin = 1.0 - t;
    //(1.0-t)*vec3f(1.f) +
    prd = tin*vec3f(1.f,1.f,1.f) + t*vec3f(0.5f,0.7f,1.0f);
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
    // the values we store the PRD pointer in:
    uint32_t u0, u1;
    packPointer( &rayColorPRD, u0, u1 );

    // normalized screen plane position, in [0,1]^2
    vec2f screen = vec2f(0.f);
    
    // generate ray direction
    vec3f rayDir = vec3f(0.f);
    
    const int samples_per_pixel = 100;

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    for (int s = 0; s < samples_per_pixel; s++)
    {
      float rx = rnd( seed );
      float ry = rnd( seed );

      screen = vec2f(rx+ix+.5f,ry+iy+.5f)
                       / vec2f(optixLaunchParams.frame.size);

      rayDir = normalize(camera.direction
                             + (screen.x - 0.5f) * camera.horizontal
                             + (screen.y - 0.5f) * camera.vertical);
      optixTrace(optixLaunchParams.traversable,
                camera.position,
                rayDir,
                0.f,    // tmin
                1e20f,  // tmax
                0.0f,   // rayTime
                OptixVisibilityMask( 255 ),
                OPTIX_RAY_FLAG_DISABLE_ANYHIT,//OPTIX_RAY_FLAG_NONE,
                SURFACE_RAY_TYPE,             // SBT offset
                RAY_TYPE_COUNT,               // SBT stride
                SURFACE_RAY_TYPE,             // missSBTIndex 
                u0, u1 );
      r += rayColorPRD.x;
      g += rayColorPRD.y;
      b += rayColorPRD.z; 
    }
    // scale by the number of samples, then scale to 256
    const int r_out = int(r/samples_per_pixel * 255.99f);
    const int g_out = int(g/samples_per_pixel * 255.99f);
    const int b_out = int(b/samples_per_pixel * 255.99f);

    // convert to 32-bit rgba value (we explicitly set alpha to 0xff
    // to make stb_image_write happy ...
    const uint32_t rgba = 0xff000000
      | (r_out<<0) | (g_out<<8) | (b_out<<16);

    // and write to frame buffer ...
    
    optixLaunchParams.frame.colorBuffer[fbIndex] = rgba;
  }
  
} // ::osc
