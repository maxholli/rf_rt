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

// #include "worlds/norlin_quad.h"
// #include "worlds/proposal.h"
// #include "worlds/norlin_quad_rf.h"
// #include "worlds/floating_square.h"
// #include "worlds/floating_triangle.h"
// // #include "worlds/cornell_box.h"
// #include "worlds/three_marbles_worship.h"
// #include "worlds/boulder_creek.h"
// #include "worlds/summer_region_20m.h"
#include "worlds/hellems.h"
// #include "worlds/hellems_ed.h"
// #include "worlds/new_hellems_arap.h"
// #include "worlds/boulder_creek_5m.h"
// #include "worlds/full_summer_12m.h"

#include <iostream>
#include <string>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include <fstream>
#include <regex>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
// #include <stdlib.h>
// #include <time.h>


int read_world_from_file(hittable_list& world, std::string filename)
{
    // ground
    auto material_s2 = make_shared<lambertian>(color(0.37, 0.37, 0.37));

    // buildings
    auto material_s1 = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    
    std::fstream newfile;
    newfile.open(filename, std::ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) //checking whether the file is open
    { 
        std::string tp;
        int tris_added = 0;
        while(std::getline(newfile, tp)){ //read data from file object and put it into string.
            tris_added++;
            if (tris_added % 1000 == 0)
                std::cerr << "\rTriangles added: " << tris_added << ' ' << std::flush;
            // world.add(make_shared<triangle>(point3(-54.106,1652.930,59.441), point3(-56.532,1652.930,62.173), point3(-56.532,1664.818,62.17), material_s1));
            std::regex str_expr (".*world\\.add.*point3\\((.*),(.*),(.*)\\), point3\\((.*),(.*),(.*)\\), point3\\((.*),(.*),(.*)\\), (.*)\\)\\);.*");
            std::smatch sm;
            if (std::regex_match(tp, sm, str_expr))
            {
                // std::cout << "we have a match\n";
                // std::cout << sm.size() << '\n';
                // std::cout << sm[0] << '\n';
                // std::cout << sm[1] << '\n';
                // std::cout << sm[2] << '\n';
                // std::cout << sm[3] << '\n';
                // std::cout << sm[4] << '\n';
                // std::cout << sm[5] << '\n';
                // std::cout << sm[6] << '\n';
                // std::cout << sm[7] << '\n';
                // std::cout << sm[8] << '\n';
                // std::cout << sm[9] << '\n';
                // std::cout << sm[10] << '\n';
                if (sm[10] == "material_s1")
                {
                    world.add(make_shared<triangle>(point3(std::stod(sm[1]),std::stod(sm[2]),std::stod(sm[3])), point3(std::stod(sm[4]),std::stod(sm[5]),std::stod(sm[6])), point3(std::stod(sm[7]),std::stod(sm[8]),std::stod(sm[9])), material_s1));
                } else if (sm[10] == "material_s2")
                {
                    world.add(make_shared<triangle>(point3(std::stod(sm[1]),std::stod(sm[2]),std::stod(sm[3])), point3(std::stod(sm[4]),std::stod(sm[5]),std::stod(sm[6])), point3(std::stod(sm[7]),std::stod(sm[8]),std::stod(sm[9])), material_s2));
                } else 
                {
                std::cerr << "ERROR: unknown material "  << sm[10] << '\n';
                }
            } 
            // else {
            //     std::cerr << "ERROR: THE LINE WASN'T A MATCH" << '\n' << tp << '\n';
            // }
            
            
        }
        newfile.close(); //close the file object.
        std::cerr << "\nWorld built\n";
    }
    return 1;
}

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
    int max_depth = 3;
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

    switch (0)
    {
        case 0:
            // for generating an image
            // world = full_summer_12m(); 
            
            read_world_from_file(world, "worlds/full_summer_12m.txt");
            std::cerr << world.objects.size() << " triangles in the world\n";
            
            // aspect_ratio = 16.0 / 9.0;
            aspect_ratio = 12.0 / 9.0;
            image_width = 200;
            image_height = static_cast<int>(image_width / aspect_ratio);
            samples_per_pixel = 3;
            max_depth = 10;
            // overhead view from south
            background = color(176.0/256, 203.0/256, 247.0/256);
            
            lookfrom = point3(100,2050,750);
            lookat = point3(1000,1663,750);
            
            // hellems
            // lookfrom = point3(100,1680,115);
            // lookat = point3(125,1663,115);
            // arapaho
            // lookfrom = point3(970,1617,750);
            // lookat = point3(940,1618,720);
            vfov = 56.0;
            
            antenna_lookfrom = lookfrom;
            num_rf_rays = 1000000;
            r_width = 2.0;
            break;
            
        case 1:
            // for rf modeling
            world = hellems(); 
            aspect_ratio = 16.0 / 9.0;
            image_width = 250;
            image_height = static_cast<int>(image_width / aspect_ratio);
            samples_per_pixel = 5;
            max_depth = 2;
            background = color(176.0/256, 203.0/256, 247.0/256);

            lookfrom = point3(16,10,80);
            lookat = point3(145,-30,110);
            vfov = 56.0;
            
            antenna_lookfrom = lookfrom;
            num_rf_rays = 1000000;
            r_width = 2.0;
            break;
            
    }


    bool render_image = true;
    bool do_rf_model = false;
    bool print_ray_history = false;
    
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
            // if (r.dir.y() > 0.05 || r.dir.y() < -0.05)
            //     continue;

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