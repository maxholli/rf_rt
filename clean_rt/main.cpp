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
#include "headers/ray_data.h"
#include "headers/rho_phi.h"

// #include "worlds/norlin_quad.h"
// #include "worlds/norlin_quad_rf.h"
// #include "worlds/floating_square.h"
// #include "worlds/floating_triangle.h"
// // #include "worlds/cornell_box.h"
// #include "worlds/three_marbles_worship.h"
#include "worlds/empty.h"
#include "worlds/ground_only.h"
#include "worlds/ground_wall.h"

#include <iostream>
#include <string>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include <complex>
#include <map>

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
        ray_history->add(rec.p, true, 0.0, emitted);
        return emitted;
    }

    // std::cout << attenuation << '\n';
    ray_history->add(rec.p, false, dot(scattered.direction(), rec.normal), attenuation);
    return emitted + attenuation * ray_color(scattered, background, world, depth-1, ray_history);
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
    double f = 900000000;
    double c = 299792458;
    float lamb = c / f;

    color background = color(0.70, 0.80, 1.00); // default light blue
    // color background = color(0, 0, 0);

    double receive_center_z = std::stod(argv[1]);
    double ground_dist = receive_center_z;
    double receiver_height = 5;
    double transmit_height = 50;
    double LOS_dist = sqrt(pow(ground_dist,2) + pow(transmit_height-receiver_height,2));
    double bounce_dist = sqrt(pow(ground_dist,2) + pow(transmit_height+receiver_height,2));
    double radius_scale_factor = 200;
    double r_frac = sqrt(1/M_PI)/radius_scale_factor;
    double receive_radius = sqrt(1/M_PI);
    // double receive_radius = r_frac*LOS_dist;
    ray_data ray_data_list;
    // unique ray path dictionary for hit point3s
    std::map<std::string, std::vector<std::vector<point3>>> uni_ray_d;
    // unique ray path dictionary for ground constant point3s
    std::map<std::string, std::vector<color>> uni_ground_d;
    // unique ray path dictionary for psi doubles
    std::map<std::string, std::vector<std::vector<double>>> uni_psi_d;
    
    std::map<std::string, ray_path_rho_phi> uni_ray_paths;

    switch (0)
    {
        case 0:
            world = ground_wall(receive_center_z, receive_radius, receiver_height);
            background = color(0,0,0);
            lookfrom = point3(0, transmit_height, 0);
            lookat = point3(0, 0, 10);
            antenna_lookfrom = lookfrom;
            num_rf_rays = std::stoull(argv[2]);
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
            if (r.dir.x() < -0.23 || r.dir.x() > 0.99 )
                continue;
            bounce_hist ray_history;

            pixel_color += ray_color(r, background, world, max_depth, &ray_history);

            if (print_ray_history) {  
                if (ray_history.hit_points.size() > 0)
                {   
                    if (ray_history.hit_points.at(ray_history.hit_points.size()-1).is_source == true)
                    {  
                        // create a point bool for the TX point
                        point_bool camera_loc;
                        camera_loc.hit = lookfrom;
                        camera_loc.is_source = false;
                        camera_loc.psi = 0;
                        camera_loc.ground_const = color(0,0,0);
                        // add TX point to the beginning of the ray_history vector
                        std::vector<point_bool>::iterator it;
                        it = ray_history.hit_points.begin();
                        ray_history.hit_points.insert(it, camera_loc);
                        
                        // get the ray path string
                        std::string ray_path_str("");
                        int num_bounces = 0;
                        for (const auto& hit_point : ray_history.hit_points) 
                        {
                            int surface_id = static_cast<int>(hit_point.ground_const.z());
                            // std::cout << " hit p = " << hit_point.hit << " " << hit_point.surface_id << " source? = " << hit_point.is_source << " " << std::endl;
                            if (surface_id != 0) // 0 is the TX point
                            {
                                ray_path_str.append(std::to_string(surface_id));
                                ray_path_str.append(",");
                                num_bounces++;
                            }
                        }
                        // int num_points_in_path = static_cast<int>(ray_history.hit_points.size());
       
                        // float cur_path_length = path_length(ray_history);
                        // // av_path_length = av_path_length + cur_path_length;
                        // std::cout << "str = " << ray_path_str << std::endl;
                        // std::cout << "path length = " << cur_path_length << std::endl;
                        // std::cout << "initial direction = " << r.dir.x() << " " << r.dir.y() << " " << r.dir.z() << '\n' << std::endl;

                        // add the ray path string to the dictionary if it's not already there
                        // inicialize the vectors (within the dictionary, 1 vector for each bounce in the path) that will hold the points 
                        if (uni_ray_d.count(ray_path_str) == 0) // check if key exists in dictionary
                        {
                            for (int bounce_i = 0; bounce_i < num_bounces; bounce_i++)
                            {
                                std::vector<point3> point_v_x;
                                uni_ray_d[ray_path_str].push_back(point_v_x);
                                std::vector<double> psi_v_x;
                                uni_psi_d[ray_path_str].push_back(psi_v_x);

                            }
                        }

                        // CLEANER
                        if (uni_ray_paths.count(ray_path_str) == 0)
                        {
                            ray_path_rho_phi new_rho_phi(num_bounces);
                            uni_ray_paths[ray_path_str] = new_rho_phi;
                            std::cerr << "building dictionary num_bounces = " << uni_ray_paths[ray_path_str].num_bounces_in_path << '\n';
                        }


                        // add the hit points to the dictionary
                        // add the psi's to the dictionary
                        num_bounces = 0;
                        for (const auto& hit_point : ray_history.hit_points) 
                        {
                            int surface_id = static_cast<int>(hit_point.ground_const.z());
                            if (surface_id != 0) // 0 is the TX point
                            {
                                uni_ray_d[ray_path_str][num_bounces].push_back(hit_point.hit);
                                uni_psi_d[ray_path_str][num_bounces].push_back(hit_point.psi);
                                num_bounces++;
                                
                            }
                        }

                        // add ground constants to dictionary
                        if (uni_ground_d.count(ray_path_str) == 0) // check if key exists in dictionary
                        {
                            for (const auto& hit_point : ray_history.hit_points)
                            {
                                int surface_id = static_cast<int>(hit_point.ground_const.z());
                                if (surface_id != 0) // 0 is the TX point
                                    uni_ground_d[ray_path_str].push_back(hit_point.ground_const);
                            }
                        }
                    }
                } 
            }
        }


        // Step 1: average the hit locations to get the average ray path.

        // something to hold the averaged segment end points
        // std::map<std::string, std::vector<point3>>
        std::map<std::string, std::vector<point3>> avr_segment_d;
        std::map<std::string, int> ray_path_hits_d;

        std::map<std::string,  std::vector<std::vector<point3>>>::iterator sp_itr;
        for (sp_itr = uni_ray_d.begin(); sp_itr != uni_ray_d.end(); ++sp_itr) // for key, example '3,2,1,'
        {
            // for unique ray path;; sp_itr->first is the unique ray path
            std::cerr << sp_itr->first << '\n';
            int num_segments = sp_itr->second.size();
            int current_segment = 0;
            ray_path_hits_d[sp_itr->first] = sp_itr->second[0].size(); // gets the number of rays that took that path
            for (const auto& inner_a : sp_itr->second) // for each list in the value, e.g. [[hit,hit], [hit,hit], [hit,hit]] 
            {
                
                if (current_segment == num_segments-1) // if hitting the RX, doen't average just give the RX location
                {
                    std::cerr << 0 << '\n';
                    std::cerr << receiver_height << '\n';
                    std::cerr << receive_center_z << '\n';
                    avr_segment_d[sp_itr->first].push_back(point3(0, receiver_height, receive_center_z));
                    
                } else {
                    double x_sum = 0;
                    double y_sum = 0;
                    double z_sum = 0;
                    int num_hits = inner_a.size();
                    // for hit in the ray path
                    for (const auto& point : inner_a)
                    {
                        // for invidual hit 
                        // std::cout << sp_itr->first << "  " << point << '\n';
                        x_sum = x_sum + point.x();
                        y_sum = y_sum + point.y();
                        z_sum = z_sum + point.z();
                    }
                    std::cerr << x_sum/num_hits << '\n';
                    std::cerr << y_sum/num_hits << '\n';
                    std::cerr << z_sum/num_hits << '\n';
                    avr_segment_d[sp_itr->first].push_back(point3(x_sum/num_hits, y_sum/num_hits, z_sum/num_hits));
                }
                current_segment++;
                std::cerr << '\n';
                
            }
            std::cerr << '\n';
        }


        // STEP 2; average the psi together for each hit location in the ray path.
        // if one day you want to know the incoming angle at the RX antenna, start here, but remember the psi is relative to the surface normal
        std::map<std::string, std::vector<double>> avr_psi_d;

        std::map<std::string,  std::vector<std::vector<double>>>::iterator psi_itr;
        for (psi_itr = uni_psi_d.begin(); psi_itr != uni_psi_d.end(); ++psi_itr) // for key, example '3,2,1,'
        {
            // for unique ray path;; psi_itr->first is the unique ray path
            std::cerr << psi_itr->first << '\n';
            // int num_segments = psi_itr->second.size();
            // int current_segment = 0;
            ray_path_hits_d[psi_itr->first] = psi_itr->second[0].size(); // gets the number of rays that took that path
            for (const auto& inner_a : psi_itr->second) // for each list in the value, e.g. [[psi,psi], [psi,psi], [psi,psi]] 
            {                                           // inner_a is the array holding psi's e.g., [psi,psi]
                // if (current_segment == num_segments-1) // if hitting the RX, doen't average just give the RX location
                // {
                // } 
                double psi_sum = 0;
                int num_hits = inner_a.size();
                // for hit in the ray path
                for (const auto& hit_psi : inner_a) // average the psi's for that hit location
                    psi_sum = psi_sum + hit_psi;

                std::cerr << "average psi = " << psi_sum/num_hits << '\n';
                avr_psi_d[psi_itr->first].push_back(psi_sum/num_hits);
                // current_segment++;
                std::cerr << '\n';
            }
            std::cerr << '\n';
        }


        double epsilon_fs = 8.8541878128e-12; // dielectric constant of free space
        double omega = 2 * M_PI * f;


        std::complex<double> total_phase1 = 0.0 + 0.0i; // from unique rays
        std::complex<double> ray_snapshot = 0.0 + 0.0i; // from unique rays
        std::map<std::string, std::vector<point3>>::iterator avr_itr;
        for (avr_itr = avr_segment_d.begin(); avr_itr != avr_segment_d.end(); ++avr_itr)
        {
            if (avr_itr->first == "3,2,1,")
                continue;

            // figure out Rho here
            double mag_rho_product = 1;
            double pha_rho_sum = 0;
            std::cerr << "calculating RHO for path " << avr_itr->first << " num hops " << avr_psi_d[avr_itr->first].size() << '\n';
            for (int i = 0; i < avr_psi_d[avr_itr->first].size()-1; i++) // w/o the -1 you go to the RX hit which doesn't have a RHO
            {
                std::cerr << "sigma " << uni_ground_d[avr_itr->first][i].y() << '\n';
                std::cerr << "epsilon " << uni_ground_d[avr_itr->first][i].x() << '\n';
                std::cerr << "average PSI " << avr_psi_d[avr_itr->first][i] << '\n';
                double epsilon = uni_ground_d[avr_itr->first][i].x(); // dielectric constant of the ground
                double sigma = uni_ground_d[avr_itr->first][i].y(); // conductivity of the ground
                double psi_rad = avr_psi_d[avr_itr->first][i];
                double x = sigma / (omega * epsilon_fs);
                std::complex<double> comp_part = epsilon - 1i*x;


                std::complex<double> rnum = 0.0 + 0.0i;
                std::complex<double> rden = 0.0 + 0.0i;
                // horizontal surfaces have EVEN surface_id (therefore use vertical polarization)
                // vertical surfaces have ODD surface_id (therefore use horizontal)
                int surface_id = static_cast<int>(uni_ground_d[avr_itr->first][i].z());
                if (surface_id % 2 == 0) // horizontal surface, so use vertical polarization
                {
                    rnum = comp_part * sin(psi_rad) - sqrt(comp_part - pow(cos(psi_rad),2));
                    rden = comp_part * sin(psi_rad) + sqrt(comp_part - pow(cos(psi_rad),2));
                }
                else
                {
                    rnum = sin(psi_rad) - sqrt(comp_part - pow(cos(psi_rad),2));
                    rden = sin(psi_rad) + sqrt(comp_part - pow(cos(psi_rad),2));
                }
                std::complex<double> rho_v = rnum / rden;
                std::cerr << "reflection coefficient " << rho_v << "\n";
                double mag_rho = sqrt(pow(real(rho_v),2) + pow(imag(rho_v),2));
                double pha_rho = -1*acos(real(rho_v) / mag_rho);
                mag_rho_product = mag_rho_product * mag_rho; // product up the magnitudes
                pha_rho_sum = pha_rho_sum + pha_rho; // sum up the phases 
            }

            // figure out arrival phase
            double r_len = 0;
            point3 cur_point = antenna_lookfrom;
            for (const auto& npoint : avr_itr->second)
            {
                r_len = r_len + distance_between(cur_point, npoint);
                std::cerr << avr_itr->first << "  " << npoint << '\n';
                cur_point = npoint;
            }
            std::cerr << "len = " << r_len << '\n';
            double phi = (r_len / lamb) * 2*M_PI + pha_rho_sum;
            std::complex<double> comp_phase = cos(phi) + 1i*sin(phi);
            total_phase1 = total_phase1 + comp_phase;
            std::cerr << "complex_phase = " << comp_phase << std::endl;
            std::cerr << "ray count = " << ray_path_hits_d[avr_itr->first] << std::endl;
            std::cerr << std::endl;

            // figure out the arrival amplitude
            // phi is the phase
            double Qinv = num_rf_rays / ray_path_hits_d[avr_itr->first];
            double amp = lamb * (1/(4*M_PI*sqrt(Qinv/(4*M_PI)))) * mag_rho_product;
            std::complex<double> ray_cluster = amp * cos(phi) + amp * 1i*sin(phi);
            ray_snapshot = ray_snapshot + ray_cluster;
        }

        double mag_all_rays = pow(real(ray_snapshot),2)+pow(imag(ray_snapshot),2);
        double dB_all_rays = 10 * log10(mag_all_rays);
        std::cout << ground_dist << ", " << dB_all_rays << "\n";


        std::cerr << "LOS ray actual " << LOS_dist << "\n";
        std::cerr << "Bounce ray length actual " << bounce_dist << "\n";

        double mag_phase1 = pow(abs(total_phase1), 2);
        std::cerr << "magnitude of phase = " << mag_phase1 << "\n";

        std::cerr << dB_all_rays << " dB is the final result\n";


        

    }

}