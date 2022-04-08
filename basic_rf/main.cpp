#include "headers/rtweekend.h"

#include "headers/color.h"
#include "headers/hittable_list.h"
#include "headers/sphere.h"
#include "headers/camera.h"
#include "headers/material.h"
// #include "headers/aarect.h"
// #include "headers/box.h"
#include "headers/bounce_hist.h"
#include "headers/triangle.h"
#include "headers/isotropic_antenna.h"
#include "headers/aabb.h"
#include "headers/bvh.h"

#include "worlds/norlin_quad.h"
#include "worlds/norlin_quad_rf.h"
#include "worlds/floating_square.h"
#include "worlds/floating_triangle.h"
// #include "worlds/cornell_box.h"
#include "worlds/three_marbles_worship.h"

#include <iostream>
#include <string>
#include <chrono>
#include <sys/time.h>
#include <ctime>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
// #include <stdlib.h>
// #include <time.h>


color ray_color(const ray& r, const color& background, const hittable& world, int depth, bounce_hist* ray_history)
{   
    // if we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);
    
    hit_record rec;
    // if the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, inifinity, rec)) 
        return background;

    // std::cout << rec.p << " ";

    // std::cout << "ray direction = " << r.dir << " " << std::endl;


    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
    {
        ray_history->add(rec.p, true);
        return emitted;
    }

    ray_history->add(rec.p, false);
    return emitted + attenuation * ray_color(scattered, background, world, depth-1, ray_history);
}


std::string ray_string(const ray& r, const color& background, const hittable& world, int depth)
{   
    // // if we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return " d-end|";
    
    hit_record rec;
    // if the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, inifinity, rec)) 
    {
        // std::cout << "B-" << depth << ' ';
        return " owild|";
    }
    
    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
    {
        // Hits the transmitting antenna
        std::string s1("");
        s1.append(" emitted=(");
        s1.append(std::to_string(emitted.x()));
        s1.append(",");
        s1.append(std::to_string(emitted.y()));
        s1.append(",");
        s1.append(std::to_string(emitted.z()));
        s1.append(") |");
        return s1;
    }

    
    std::string s1("");
    s1.append(" emitted=(");
    s1.append(std::to_string(emitted.x()));
    s1.append(",");
    s1.append(std::to_string(emitted.y()));
    s1.append(",");
    s1.append(std::to_string(emitted.z()));
    s1.append(")+attenuation=(");
    s1.append(std::to_string(attenuation.x()));
    s1.append(",");
    s1.append(std::to_string(attenuation.y()));
    s1.append(",");
    s1.append(std::to_string(attenuation.z()));
    s1.append(") ");    
    return s1.append(ray_string(scattered, background, world, depth-1));
}


double path_length(bounce_hist ray_hist)
{
    double path_len = 0.0;
    for (int i = 0; i < static_cast<int>(ray_hist.hit_points.size()) - 1; i++)
    {
        path_len += distance_between(ray_hist.hit_points.at(i).hit, ray_hist.hit_points.at(i+1).hit);
    }
    return path_len;
}

int main()
{
    srand(time(NULL));

    // image
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 1000;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    int samples_per_pixel = 100;
    const int max_depth = 10;
    int num_rf_rays = 100000;
    // World
    hittable_list world;
    point3 lookfrom;
    point3 lookat;
    point3 antenna_lookfrom;
    double vfov;
    double r_width = 1.0;
    

    color background = color(0.70, 0.80, 1.00); // default light blue
    // color background = color(0, 0, 0);

    switch (5)
    {
        case 0:
            world = three_marbles_worship();
            aspect_ratio = 16.0 / 9.0;
            image_width = 400;
            image_height = static_cast<int>(image_width / aspect_ratio);
            samples_per_pixel = 50;
            background = color(0, 0, 0);
            lookfrom = point3(-0.5,2,2);
            lookat = point3(0,0,-1);
            vfov = 90.0;

            antenna_lookfrom = lookfrom;
            num_rf_rays = 500;
            break;
        case 1:
            // world = cornell_box();
            aspect_ratio = 1.0;
            image_width = 600;
            image_height = static_cast<int>(image_width / aspect_ratio);
            samples_per_pixel = 1;
            background = color(0,0,0);
            lookfrom = point3(278, 278, -800);
            lookat = point3(278, 278, 0);
            vfov = 40.0;
            antenna_lookfrom = lookfrom;
            num_rf_rays = 10000;
            break;
        case 2:
            world = floating_square();
            aspect_ratio = 1.0;
            image_width = 30;
            image_height = static_cast<int>(image_width / aspect_ratio);
            samples_per_pixel = 1;
            background = color(0.70, 0.80, 1.00);
            lookfrom = point3(0,2,2);
            lookat = point3(0,2,-1);
            vfov = 90.0;
            antenna_lookfrom = lookfrom;
            num_rf_rays = 10000;
            break;
        case 3:
            world = floating_triangle();
            aspect_ratio = 1.0;
            image_width = 200;
            image_height = static_cast<int>(image_width / aspect_ratio);
            samples_per_pixel = 1;
            background = color(0.70, 0.80, 1.00);
            lookfrom = point3(0,2,2);
            lookat = point3(0,2,-2);
            vfov = 90.0;
            antenna_lookfrom = lookfrom;
            num_rf_rays = 10000;
            break;
        case 4:
            // for generating an image
            world = norlin_quad(); 
            aspect_ratio = 16.0 / 9.0;
            image_width = 500;
            image_height = static_cast<int>(image_width / aspect_ratio);
            samples_per_pixel = 10;
            
            // overhead view from south
            background = color(176.0/256, 203.0/256, 247.0/256);
            lookfrom = point3(290,300,50);
            lookat = point3(290,15,-135);
            vfov = 56.0;

            // rx looking down norlin quad
            // background = color(0, 0, 0);
            // lookfrom = point3(140,10,-260);
            // lookat = point3(300,10,-260);
            // vfov = 90.0;
            
            antenna_lookfrom = lookfrom;
            num_rf_rays = 1000000;
            r_width = 2.0;
            break;

        case 5:
            // for rf_modeling
            world = norlin_quad_rf(); 
            aspect_ratio = 16.0 / 9.0;
            image_width = 500;
            image_height = static_cast<int>(image_width / aspect_ratio);
            samples_per_pixel = 10;

            // rx looking down norlin quad
            background = color(0, 0, 0);
            lookfrom = point3(140,10,-260);
            lookat = point3(300,10,-260);
            vfov = 90.0;
            
            antenna_lookfrom = lookfrom;
            num_rf_rays = 10000;
            r_width = 2.0;
            break;
    }


    bool render_image = false;
    bool do_rf_model = true;
    bool print_ray_history = true;
    
    if (do_rf_model)
    {
        // antenna
        iso_antenna antenna(antenna_lookfrom);
        // model
        for (int i = 0; i < num_rf_rays; i++)
        {
            if (i % 10000 == 0)  
                std::cerr << "\rRays remaining: " << num_rf_rays - i << ' ' << std::flush;
            color pixel_color(0,0,0);
            // do another for loop here for samples per pixel
            ray r = antenna.get_ray();
            if (r.dir.y() > 0.05 || r.dir.y() < -0.05)
                continue;

            bounce_hist ray_history;

            pixel_color += ray_color(r, background, world, max_depth, &ray_history);

            if (print_ray_history) {  
                if (ray_history.hit_points.size() > 0)
                {
                    if (ray_history.hit_points.at(ray_history.hit_points.size()-1).is_source == true)
                    {  
                        point_bool camera_loc;
                        camera_loc.hit = lookfrom;
                        camera_loc.is_source = false;
                        std::vector<point_bool>::iterator it;
                        it = ray_history.hit_points.begin();
                        ray_history.hit_points.insert(it, camera_loc);
                        // for (const auto& hit_point : ray_history.hit_points) 
                        // {
                        //     std::cout << " hit p = " << hit_point.hit << " source? = " << hit_point.is_source << " " << std::endl;
                        // }
                        int num_points_in_path = static_cast<int>(ray_history.hit_points.size());
                        for (int r_i = 0; r_i < num_points_in_path-1; r_i++)
                        {
                            // std::cout << " hit p = " << ray_history.hit_points[r_i].hit << " source? = " << ray_history.hit_points[r_i].is_source << " " << std::endl;
                            vec3 y_adj(0,r_width/2.0,0);
                            // world.add(make_shared<triangle>(point3(230.57,20.00,-6.80), point3(237.72,20.00,-17.53), point3(237.72,0.00,-17.53), material_s1));
                            std::cout << "world.add(make_shared<triangle>(point3(" << ray_history.hit_points[r_i].hit - y_adj 
                                        << "), point3(" << ray_history.hit_points[r_i+1].hit - y_adj 
                                        << "), point3(" << ray_history.hit_points[r_i].hit + y_adj
                                        << "), material_s2));" << std::endl;
                            std::cout << "world.add(make_shared<triangle>(point3(" << ray_history.hit_points[r_i].hit + y_adj 
                                        << "), point3(" << ray_history.hit_points[r_i+1].hit + y_adj 
                                        << "), point3(" << ray_history.hit_points[r_i+1].hit - y_adj
                                        << "), material_s2));" << std::endl;
                        
                        }             
                        // std::cout << "path length = " << path_length(ray_history) << '\n' << std::endl;
                    }
                } 
            }
        }
        std::cerr << "\nDone.\n";
    }


    if (render_image)
    {
        // camera
        camera cam(lookfrom, lookat, vec3(0,1,0), vfov, aspect_ratio);
        // Render
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        auto millisec_start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        for (int j = image_height-1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0,0,0);
                for (int s=0; s < samples_per_pixel; s++)
                {
                    // auto u = (i+random_double(0,0.01)) / (image_width-1);
                    // auto v = (j+random_double(0,0.01)) / (image_height-1);
                    auto u = (i+random_double(0,0.99)) / (image_width-1);
                    auto v = (j+random_double(0,0.99)) / (image_height-1);
                    ray r = cam.get_ray(u, v);
                    bounce_hist ray_history;
                    
                    pixel_color += ray_color(r, background, world, max_depth, &ray_history);

                    if (print_ray_history) {  
                        if (ray_history.hit_points.size() > 0)
                        {
                            if (ray_history.hit_points.at(ray_history.hit_points.size()-1).is_source == true)
                            {  
                                point_bool camera_loc;
                                camera_loc.hit = lookfrom;
                                camera_loc.is_source = false;
                                std::vector<point_bool>::iterator it;
                                it = ray_history.hit_points.begin();
                                ray_history.hit_points.insert(it, camera_loc);
                                for (const auto& hit_point : ray_history.hit_points)
                                {
                                    std::cout << " hit p = " << hit_point.hit << " source? = " << hit_point.is_source << " " << std::endl;
                                }                
                                std::cout << "path length = " << path_length(ray_history) << '\n' << std::endl;
                            }
                        } 
                    }
                    // std::cout << "||";        
                }
                // std::cout << '\n';
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
            // std::cout << '\n';
        }
        auto millisec_stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        std::cerr << "\nDone.\nRays shot = "
                    << image_height * image_width * samples_per_pixel
                    << "\nDuration in ms = "
                    << millisec_stop - millisec_start 
                    << std::endl;
    } // end -> if (render_image) 



}