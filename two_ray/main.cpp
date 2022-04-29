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
// #include "worlds/norlin_quad_rf.h"
// #include "worlds/floating_square.h"
// #include "worlds/floating_triangle.h"
// // #include "worlds/cornell_box.h"
// #include "worlds/three_marbles_worship.h"
#include "worlds/empty.h"
#include "worlds/ground_only.h"

#include <iostream>
#include <string>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include <complex>

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
        ray_history->add(rec.p, true, 0.0);
        return emitted;
    }

    ray_history->add(rec.p, false, dot(scattered.direction(), rec.normal));
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
    using namespace std::complex_literals;
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
    double ground_dist = receive_center_z;
    double receiver_height = 5;
    double transmit_height = 50;
    double LOS_dist = sqrt(pow(ground_dist,2) + pow(transmit_height-receiver_height,2));
    double radius_scale_factor = 200;
    double r_frac = sqrt(1/M_PI)/radius_scale_factor;
    //double receive_radius = sqrt(1/M_PI);
    double receive_radius = r_frac*LOS_dist;
    
    switch (0)
    {
        case 0:
            world = ground_only(receive_center_z, receive_radius, receiver_height);
            background = color(0,0,0);
            lookfrom = point3(0, transmit_height, 0);
            lookat = point3(0, 0, 10);
            antenna_lookfrom = lookfrom;
            num_rf_rays = 1e9;
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
        // int hit_count = 0;
        // float av_path_length = 0;
        
        int hit_1_count = 0;
        int hit_2_count = 0;
        float ave_1_leng = 0;
        float ave_2_leng = 0;
        double ave_psi = 0;
        color ground_properties(0,0,0);
        
        for (uint64_t i = 0; i < num_rf_rays; i++)
        {
            // if (i % 1000000 == 0)  
            //     std::cerr << "\rRays remaining: " << num_rf_rays - i << ' ' << std::flush;
            color pixel_color(0,0,0);
            // do another for loop here for samples per pixel
            ray r = antenna.get_ray();
                
            if (r.dir.y() > 0.002)
                continue;
            if (r.dir.z() < -0.005)
                continue;
            if (r.dir.x() < -0.23 || r.dir.x() > 0.23 )
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
                        // int num_points_in_path = static_cast<int>(ray_history.hit_points.size());
       
                        // float cur_path_length = path_length(ray_history);
                        // av_path_length = av_path_length + cur_path_length;
                        // std::cout << "path length = " << cur_path_length << std::endl;
                        // std::cout << "initial direction = " << r.dir.x() << " " << r.dir.y() << " " << r.dir.z() << '\n' << std::endl;
                        if (ray_history.hit_points.size() == 2)
                        {
                            // LOS rays
                            hit_1_count++;
                            ave_1_leng = ave_1_leng + path_length(ray_history);
                        }
                        else if (ray_history.hit_points.size() == 3)
                        {
                            // Ground bounce rays
                            hit_2_count++;
                            ave_2_leng = ave_2_leng + path_length(ray_history);
                            ground_properties = pixel_color;
                            ave_psi = ave_psi + ray_history.hit_points[1].psi;
                        }
                    }
                } 
            }
        }
        double modifier = 0.564189584 * 0.679;
        double leng_1 = ave_1_leng/hit_1_count + modifier;
        double leng_2 = ave_2_leng/hit_2_count + modifier;
        double psi_rad = ave_psi/hit_2_count;
        std::cerr << "\nDone.\n";
        // std::cerr << argv[1] << "\n";
        std::cerr << "average psi " << psi_rad << "\n";
        std::cerr << "LOS hits " << hit_1_count << "\n";
        std::cerr << "LOS ray length " << leng_1 << "\n";
        std::cerr << "Bounce hits " << hit_2_count << "\n";
        std::cerr << "Bounce ray length " << leng_2 << "\n";
    

        double epsilon = ground_properties.x(); // dielectric constant of the ground
        double sigma = ground_properties.y(); // conductivity of the ground
        double epsilon_fs = 8.8541878128e-12; // dielectric constant of free space
        double omega = 2 * M_PI * f;
        double x = sigma / (omega * epsilon_fs);

        std::complex<double> comp_part = epsilon - 1i*x;
        std::complex<double> rnum = comp_part * sin(psi_rad) - sqrt(comp_part - pow(cos(psi_rad),2));
        std::complex<double> rden = comp_part * sin(psi_rad) + sqrt(comp_part - pow(cos(psi_rad),2));
        std::complex<double> rho_v = rnum / rden;
        std::cerr << "reflection coefficient " << rho_v << "\n";

        double delta_d = leng_2 - leng_1;
        double lamb = 300000000 / f;
        double delta_phi = (2 * M_PI / lamb) * delta_d;
        std::cerr << "phase difference, radians " << delta_phi << "\n";
        std::complex<double> ce_phi = cos(delta_phi) - 1i*sin(delta_phi);
        std::cerr << "phase contribution mag " << sqrt(pow(real(ce_phi),2)+pow(imag(ce_phi),2)) << "\n";

        std::complex<double> change_E = 1.0 + 0.0i;
        change_E = change_E + rho_v * ce_phi;
        std::cerr << "change E " << change_E <<  "\n";
        double change_P = pow(real(change_E),2)+ pow(imag(change_E),2);
        std::cerr << "change P " << change_P <<  "\n";

        double Q = hit_1_count;
        Q = Q / num_rf_rays;
        Q = Q / (pow(LOS_dist,2)/pow(radius_scale_factor,2));
        double pathloss = (-10.0 * log10(Q)) + (10 * log10(4*M_PI)) + (20 * log10(f/300000000));
        std::cerr << "Path Loss " << pathloss << "\n";

        std::cerr << "ray addition alternative\n";
        double nQ = hit_1_count;
        double refl_contribution = (change_P - 1.0) * hit_2_count;
        int refl_cont_whole = round(refl_contribution);
        // double rQ = hit_1_count + refl_contribution;
        nQ = nQ + refl_cont_whole;

        nQ = nQ / num_rf_rays;
        // rQ = rQ / num_rf_rays;
        nQ = nQ/(pow(LOS_dist,2)/pow(radius_scale_factor,2));
        double pathloss_w = (-10.0 * log10(nQ)) + (10 * log10(4*M_PI)) + (20 * log10(f/300000000));
        std::cerr << "Path Loss whole numbers" << pathloss_w << "\n";
        // double pathloss_r = (-10.0 * log10(rQ)) + (10 * log10(4*M_PI)) + (20 * log10(f/300000000));
        // std::cerr << "Path Loss reals" << pathloss_r << "\n";
        std::cout << ground_dist << ", " << LOS_dist << ", " << pathloss_w << ", " << pathloss << "\n";


        // Q = Q / num_rf_rays;
        // // adjust for receiver size
        // Q = Q / (pow(LOS_dist,2)/pow(radius_scale_factor,2));
        // double fspl = (-10.0 * log10(Q)) + (10 * log10(4*M_PI)) + (20 * log10(f/300000000));
        // // std::cerr << fspl << "\n";
        // // std::cout << hit_count << " / " << num_rf_rays << "\n";
        // std::cout << receive_center_z << ", " << fspl << "\n";

    }

}