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

#include "SampleRenderer.h"

// our helper library for window handling
#include "glfWindow/GLFWindow.h"
#include <GL/gl.h>

/*! \namespace osc - Optix Siggraph Course */
namespace osc {

  struct SampleWindow : public GLFCameraWindow
  {
    SampleWindow(const std::string &title,
                 const Model *model,
                 const Camera &camera,
                 const float worldScale)
      : GLFCameraWindow(title,camera.from,camera.at,camera.up,worldScale),
        sample(model)
    {
      sample.setCamera(camera);
    }
    
    virtual void render() override
    {
      if (cameraFrame.modified) {
        sample.setCamera(Camera{ cameraFrame.get_from(),
                                 cameraFrame.get_at(),
                                 cameraFrame.get_up() });
        cameraFrame.modified = false;
      }
      sample.render();
    }
    
    virtual void draw() override
    {
      sample.downloadPixels(pixels.data());
      if (fbTexture == 0)
        glGenTextures(1, &fbTexture);
      
      glBindTexture(GL_TEXTURE_2D, fbTexture);
      GLenum texFormat = GL_RGBA;
      GLenum texelType = GL_UNSIGNED_BYTE;
      glTexImage2D(GL_TEXTURE_2D, 0, texFormat, fbSize.x, fbSize.y, 0, GL_RGBA,
                   texelType, pixels.data());

      glDisable(GL_LIGHTING);
      glColor3f(1, 1, 1);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, fbTexture);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      
      glDisable(GL_DEPTH_TEST);

      glViewport(0, 0, fbSize.x, fbSize.y);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.f, (float)fbSize.x, 0.f, (float)fbSize.y, -1.f, 1.f);

      glBegin(GL_QUADS);
      {
        glTexCoord2f(0.f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);
      
        glTexCoord2f(0.f, 1.f);
        glVertex3f(0.f, (float)fbSize.y, 0.f);
      
        glTexCoord2f(1.f, 1.f);
        glVertex3f((float)fbSize.x, (float)fbSize.y, 0.f);
      
        glTexCoord2f(1.f, 0.f);
        glVertex3f((float)fbSize.x, 0.f, 0.f);
      }
      glEnd();
    }
    
    virtual void resize(const vec2i &newSize) 
    {
      fbSize = newSize;
      sample.resize(newSize);
      pixels.resize(newSize.x*newSize.y);
    }

    vec2i                 fbSize;
    GLuint                fbTexture {0};
    SampleRenderer        sample;
    std::vector<uint32_t> pixels;
  };
  
  
  /*! main entry point to this example - initially optix, print hello
    world, then exit */
  extern "C" int main(int ac, char **av)
  {
    try {
      Model *model = loadOBJ(
#ifdef _WIN32
      // on windows, visual studio creates _two_ levels of build dir
      // (x86/Release)
      "../../models/sponza.obj"
#else
      // on linux, common practice is to have ONE level of build dir
      // (say, <project>/build/)...
      // "../models/sponza.obj"
      "../models/ec.obj"
#endif
                             );
      // standard
      Camera camera = { /*from*/vec3f(-125.f, model->bounds.center().y+100.f, model->bounds.center().z),
                        /* at */vec3f(model->bounds.center().x, model->bounds.center().y, model->bounds.center().z),
                        /* up */vec3f(0.f,1.f,0.f) };
      // centered over denver
      // Camera camera = { /*from*/vec3f(model->bounds.center().x-1000.f, 325.0f, model->bounds.center().z-10000.f),
      //                   /* at */vec3f(model->bounds.center().x, model->bounds.center().y, model->bounds.center().z-10000.f),
      //                   /* up */vec3f(0.f,1.f,0.f) };
      // centered over Boulder City
      // Camera camera = { /*from*/vec3f(-375.f, 325.0f, model->bounds.center().z),
      //                   /* at */vec3f(model->bounds.center().x-7000.f, model->bounds.center().y, model->bounds.center().z+7000.f),
      //                   /* up */vec3f(0.f,1.f,0.f) };
      //
      // Camera camera = { /*from*/vec3f(model->bounds.center().x-11000.f, 1000.0f, model->bounds.center().z+7000.f),
      //                   /* at */vec3f(model->bounds.center().x-9000.f, 10.f, model->bounds.center().z+7000.f),
      //                   /* up */vec3f(0.f,1.f,0.f) };
      // Camera camera = { /*from*/vec3f(model->bounds.center().x-9500.f, 400.0f, model->bounds.center().z+7000.f),
      //                   /* at */vec3f(model->bounds.center().x-9000.f, 10.f, model->bounds.center().z+7000.f),
      //                   /* up */vec3f(0.f,1.f,0.f) };
      // Camera camera = { /*from*/vec3f(model->bounds.center().x-11000.f, 3000.0f, model->bounds.center().z+7000.f),
      //                   /* at */vec3f(model->bounds.center().x-9000.f, 10.f, model->bounds.center().z+7000.f),
      //                   /* up */vec3f(0.f,1.f,0.f) };
      // Camera camera = { /*from*/vec3f(10.f, 5.0f, 0.f),
      //                   /* at */vec3f(model->bounds.center().x-20.f, model->bounds.center().y, model->bounds.center().z),
      //                   /* up */vec3f(0.f,1.f,0.f) };
      // something approximating the scale of the world, so the
      // camera knows how much to move for any given user interaction:
      const float worldScale = length(model->bounds.span());

      SampleWindow *window = new SampleWindow("Optix 7 Course Example",
                                              model,camera,worldScale);
      window->run();
      
    } catch (std::runtime_error& e) {
      std::cout << GDT_TERMINAL_RED << "FATAL ERROR: " << e.what()
                << GDT_TERMINAL_DEFAULT << std::endl;
	  std::cout << "Did you forget to copy sponza.obj and sponza.mtl into your optix7course/models directory?" << std::endl;
	  exit(1);
    }
    return 0;
  }
  
} // ::osc
