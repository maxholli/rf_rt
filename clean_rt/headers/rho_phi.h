#ifndef RAY_PATH_RHO_PHI_H
#define RAY_PATH_RHO_PHI_H

// #include "hittable.h"
#include "vec3.h"

#include <vector>
// #include <memory>

// using std::shared_ptr;

class vec4
{
    public:
        vec4() : e{0,0,0,0} {}
        vec4(double e0, double e1, double e2, double e3) : e{e0, e1, e2} {}

        double a() const { return e[0]; }
        double b() const { return e[1]; }
        double c() const { return e[2]; }
        double d() const { return e[3]; }

    public:
        double e[4];
};

using surface_constants = vec4;


class ray_path_rho_phi
{
    public:
        ray_path_rho_phi(int bounces) 
        {
            num_bounces_in_path = bounces;
            num_rays_in_cluster = 0;
            for (int bounce_i = 0; bounce_i < bounces; bounce_i++)
            {
                std::vector<point3> point_v_x;
                hit_points.push_back(point_v_x);
                std::vector<double> psi_v_x;
                hit_psis.push_back(psi_v_x);
            }
        }

        void clear()
        {
            hit_points.clear();
            surf_consts.clear();
            hit_psis.clear();
            avr_hit_points.clear();
            avr_hit_psis.clear();
        }

    public:
        int num_bounces_in_path;
        int num_rays_in_cluster;
        std::vector<std::vector<point3>> hit_points; //length(hit_clusters) = num_bounces_in_path, length(hit_clusters[0]) = num_rays_in_cluster
        std::vector<surface_constants> surf_consts;  //length(surf_consts) = num_bounces_in_path
        std::vector<std::vector<double>> hit_psis;    //length(hit_psis) = num_bounces_in_path, length(hit_psis[0]) = num_rays_in_cluster
        std::vector<point3> avr_hit_points;          //length(avr_hit_points) = num_bounces_in_path
        std::vector<double> avr_hit_psis;            //length(avr_hit_psis) = num_bounces_in_path

};

// struct postp_data {
//     float length;
//     // point3 hit;
//     // double psi; // the incident angle 
//     // bool is_source;
// };

// class ray_data
// {
//     public:
//         ray_data() {}
//         // bounce_hist(point_bool hit_point) { add(hit_point); }

//         void clear() { hit_data.clear(); }
//         void add(float ray_length)
//         {
//             postp_data new_data;
//             new_data.length = ray_length;
//             hit_data.push_back(new_data); 
//         }

//     public:
//         std::vector<postp_data> hit_data;
// };

#endif