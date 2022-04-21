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
#include "worlds/empty.h"

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
    uint64_t num_rf_rays = 0;
    // World
    hittable_list world;
    point3 lookfrom;
    point3 lookat;
    point3 antenna_lookfrom;
    double vfov;
    double r_width = 1.0; // ray width for image generation (triangle height)
    double f = 300000000;

    color background = color(0.70, 0.80, 1.00); // default light blue
    // color background = color(0, 0, 0);

    switch (0)
    {
        case 0:
            world = empty();
            aspect_ratio = 1.0;
            image_width = 600;
            image_height = static_cast<int>(image_width / aspect_ratio);
            samples_per_pixel = 1;
            background = color(0,0,0);
            lookfrom = point3(0, 0, 0);
            lookat = point3(0, 0, 10);
            vfov = 40.0;
            antenna_lookfrom = lookfrom;
            num_rf_rays = 1000000000;
            // num_rf_rays = 300000000;
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
        int hit_count = 0;
        float av_path_length = 0;
        for (uint64_t i = 0; i < num_rf_rays; i++)
        {
            if (i % 1000000 == 0)  
                std::cerr << "\rRays remaining: " << num_rf_rays - i << ' ' << std::flush;
            color pixel_color(0,0,0);
            // do another for loop here for samples per pixel
            ray r = antenna.get_ray();
            if (r.dir.y() > 0.02 || r.dir.y() < -0.02)
                continue;
            if (r.dir.z() < 0.98)
                continue;
            bounce_hist ray_history;

            pixel_color += ray_color(r, background, world, max_depth, &ray_history);

            if (print_ray_history) {  
                if (ray_history.hit_points.size() > 0)
                {   
                    hit_count++;
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
                        int num_points_in_path = static_cast<int>(ray_history.hit_points.size());
       
                        float cur_path_length = path_length(ray_history);
                        av_path_length = av_path_length + cur_path_length;
                        std::cout << "path length = " << cur_path_length << '\n' << std::endl;

                    }
                } 
            }
        }
        std::cerr << "\nDone.\n";
        std::cerr << hit_count << " / " << num_rf_rays << "\n";
        std::cerr << "average path length = " << av_path_length / hit_count << "\n";
        double Q = hit_count;
        Q = Q / num_rf_rays;
        double fspl = (-10.0 * log10(Q)) + (10 * log10(4*M_PI)) + (20 * log10(f/300000000));
        std::cerr << fspl << "\n";
        std::cout << hit_count << " / " << num_rf_rays << "\n";
        std::cout << fspl << "\n";
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