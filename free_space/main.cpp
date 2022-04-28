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

int main(int argc, char** argv)
{
    srand(time(NULL));

    // image
    const int max_depth = 10;
    uint64_t num_rf_rays = 0; // reset in world spec
    // World
    hittable_list world;
    point3 lookfrom;
    point3 lookat;
    point3 antenna_lookfrom;
    double f = 300000000;

    color background = color(0.70, 0.80, 1.00); // default light blue
    // color background = color(0, 0, 0);

    double receive_center_z = std::stod(argv[1]);
    double LOS_dist = receive_center_z;
    double r_frac = sqrt(1/M_PI)/200;
    //double receive_radius = sqrt(1/M_PI);
    double receive_radius = r_frac*LOS_dist;
    switch (0)
    {
        case 0:
            world = empty(receive_center_z, receive_radius);
            background = color(0,0,0);
            lookfrom = point3(0, 0, 0);
            lookat = point3(0, 0, 10);
            antenna_lookfrom = lookfrom;
            num_rf_rays = 2e7;
            // num_rf_rays = 300000000;
            break;
    }


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
            // if (i % 1000000 == 0)  
            //     std::cerr << "\rRays remaining: " << num_rf_rays - i << ' ' << std::flush;
            color pixel_color(0,0,0);
            // do another for loop here for samples per pixel
            ray r = antenna.get_ray();
            // safe for 5 meters out and beyond
            if (r.dir.y() > 0.23 || r.dir.y() < -0.23)
                continue;
            if (r.dir.z() < 0.97)
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
                        // for (const auto& hit_point : ray_history.hit_points) 
                        // {
                        //     std::cout << " hit p = " << hit_point.hit << " source? = " << hit_point.is_source << " " << std::endl;
                        // }
                        // int num_points_in_path = static_cast<int>(ray_history.hit_points.size());
       
                        // float cur_path_length = path_length(ray_history);
                        // av_path_length = av_path_length + cur_path_length;
                        // std::cout << "path length = " << cur_path_length << std::endl;
                        // std::cout << "initial direction = " << r.dir.x() << " " << r.dir.y() << " " << r.dir.z() << '\n' << std::endl;
                    }
                } 
            }
        }
        // std::cerr << "\nDone.\n";
        // std::cerr << hit_count << " / " << num_rf_rays << "\n";
        // std::cerr << "average path length = " << av_path_length / hit_count << "\n";
        double Q = hit_count;
        Q = Q / num_rf_rays;
        // adjust for receiver size
        Q = Q / (pow(LOS_dist,2)/40000);
        double fspl = (-10.0 * log10(Q)) + (10 * log10(4*M_PI)) + (20 * log10(f/300000000));
        // std::cerr << fspl << "\n";
        // std::cout << hit_count << " / " << num_rf_rays << "\n";
        std::cout << receive_center_z << ", " << fspl << "\n";

    }

}