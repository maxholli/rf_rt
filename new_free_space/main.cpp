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
       
                        float cur_path_length = path_length(ray_history);
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
                        
                        
                        
                        
                        
                        
                        // old code below
                        ray_data_list.add(cur_path_length);

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

        // std::complex<double> total_phase = 0.0 + (1.0i*0);
        std::complex<double> total_phase = 0.0 + 0.0i;

        for (const auto& ray_data_bit : ray_data_list.hit_data) 
        {
            double phi = (ray_data_bit.length / lamb) * 2*M_PI;
            // np.cos(phi) + np.sin(phi)*1j
            // std::complex<double> comp_part = epsilon - 1i*x;
            std::complex<double> comp_phase = cos(phi) + 1i*sin(phi);
            total_phase = total_phase + comp_phase;
            // std::cout << "phi = " << phi << std::endl;
        }
        // double mag_phase = pow(abs(total_phase), 2);
        // std::cout << "magnitude of phase = " << mag_phase << "\n";



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



        // double epsilon = ground_properties.x(); // dielectric constant of the ground
        // double sigma = ground_properties.y(); // conductivity of the ground
        double epsilon_fs = 8.8541878128e-12; // dielectric constant of free space
        double omega = 2 * M_PI * f;
        // double x = sigma / (omega * epsilon_fs);

        // std::complex<double> comp_part = epsilon - 1i*x;
        // std::complex<double> rnum = comp_part * sin(psi_rad) - sqrt(comp_part - pow(cos(psi_rad),2));
        // std::complex<double> rden = comp_part * sin(psi_rad) + sqrt(comp_part - pow(cos(psi_rad),2));
        // std::complex<double> rho_v = rnum / rden;
        // std::cerr << "reflection coefficient " << rho_v << "\n";

        // antenna_lookfrom
        std::complex<double> total_phase1 = 0.0 + 0.0i; // from unique rays
        std::complex<double> ray_snapshot = 0.0 + 0.0i; // from unique rays
        // std::map<std::string, std::vector<point3>> uni_ray_d;
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

        // nQ = nQ / num_rf_rays;
        // // rQ = rQ / num_rf_rays;
        // nQ = nQ/(pow(LOS_dist,2)/pow(radius_scale_factor,2));


        std::cerr << "LOS ray actual " << LOS_dist << "\n";
        // std::cerr << "Bounce hits " << hit_2_count << "\n";
        std::cerr << "Bounce ray length actual " << bounce_dist << "\n";

        double mag_phase1 = pow(abs(total_phase1), 2);
        std::cerr << "magnitude of phase = " << mag_phase1 << "\n";

        std::cerr << dB_all_rays << " dB is the final result\n";


        // // double modifier = 0.564189584 * 0.679;
        // double modifier = LOS_dist * (1.0/(2.666*radius_scale_factor)); // 267 for scale factor 100, 537 for 200, 802 for 300
        // double leng_1 = ave_1_leng/hit_1_count + modifier;
        // double leng_2 = ave_2_leng/hit_2_count + modifier;
        // double psi_rad = ave_psi/hit_2_count;
        // std::cerr << "\nDone.\n";
        // // std::cerr << argv[1] << "\n";
        // std::cerr << "average psi " << psi_rad << "\n";
        // std::cerr << "LOS hits " << hit_1_count << "\n";
        // std::cerr << "LOS ray length estm, " << leng_1 << ", actual " << LOS_dist << "\n";
        // std::cerr << "Bounce hits " << hit_2_count << "\n";
        // std::cerr << "Bounce ray length estm, " << leng_2 << ", actual " << bounce_dist << "\n";
    

        // double epsilon = ground_properties.x(); // dielectric constant of the ground
        // double sigma = ground_properties.y(); // conductivity of the ground
        // double epsilon_fs = 8.8541878128e-12; // dielectric constant of free space
        // double omega = 2 * M_PI * f;
        // double x = sigma / (omega * epsilon_fs);

        // std::complex<double> comp_part = epsilon - 1i*x;
        // std::complex<double> rnum = comp_part * sin(psi_rad) - sqrt(comp_part - pow(cos(psi_rad),2));
        // std::complex<double> rden = comp_part * sin(psi_rad) + sqrt(comp_part - pow(cos(psi_rad),2));
        // std::complex<double> rho_v = rnum / rden;
        // std::cerr << "reflection coefficient " << rho_v << "\n";

        // double delta_d = leng_2 - leng_1;
        // double lamb = 300000000 / f;
        // double delta_phi = (2 * M_PI / lamb) * delta_d;
        // std::cerr << "phase difference, radians " << delta_phi << "\n";
        // std::complex<double> ce_phi = cos(delta_phi) - 1i*sin(delta_phi);
        // std::cerr << "phase contribution mag " << sqrt(pow(real(ce_phi),2)+pow(imag(ce_phi),2)) << "\n";

        // std::complex<double> change_E = 1.0 + 0.0i;
        // change_E = change_E + rho_v * ce_phi;
        // std::cerr << "change E " << change_E <<  "\n";
        // double change_P = pow(real(change_E),2)+ pow(imag(change_E),2);
        // std::cerr << "change P " << change_P <<  "\n";

        // double Q = hit_1_count;
        // Q = Q / num_rf_rays;
        // Q = Q / (pow(LOS_dist,2)/pow(radius_scale_factor,2));
        // double pathloss = (-10.0 * log10(Q)) + (10 * log10(4*M_PI)) + (20 * log10(f/300000000));
        // std::cerr << "Path Loss " << pathloss << "\n";

        // std::cerr << "ray addition alternative\n";
        // double nQ = hit_1_count;
        // double refl_contribution = (change_P - 1.0) * hit_2_count;
        // int refl_cont_whole = round(refl_contribution);
        // // double rQ = hit_1_count + refl_contribution;
        // nQ = nQ + refl_cont_whole;

        // nQ = nQ / num_rf_rays;
        // // rQ = rQ / num_rf_rays;
        // nQ = nQ/(pow(LOS_dist,2)/pow(radius_scale_factor,2));
        // double pathloss_w = (-10.0 * log10(nQ)) + (10 * log10(4*M_PI)) + (20 * log10(f/300000000));
        // std::cerr << "Path Loss whole numbers" << pathloss_w << "\n";
        // // double pathloss_r = (-10.0 * log10(rQ)) + (10 * log10(4*M_PI)) + (20 * log10(f/300000000));
        // // std::cerr << "Path Loss reals" << pathloss_r << "\n";
        // std::cout << ground_dist << ", " << LOS_dist << ", " << pathloss_w << ", " << pathloss << "\n";


        // // Q = Q / num_rf_rays;
        // // // adjust for receiver size
        // // Q = Q / (pow(LOS_dist,2)/pow(radius_scale_factor,2));
        // // double fspl = (-10.0 * log10(Q)) + (10 * log10(4*M_PI)) + (20 * log10(f/300000000));
        // // // std::cerr << fspl << "\n";
        // // // std::cout << hit_count << " / " << num_rf_rays << "\n";
        // // std::cout << receive_center_z << ", " << fspl << "\n";

    }

}