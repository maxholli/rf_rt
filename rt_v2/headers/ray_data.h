#ifndef RAY_DATA_H
#define RAY_DATA_H

// #include "hittable.h"
// #include "vec3.h"

#include <vector>
// #include <memory>

// using std::shared_ptr;

struct postp_data {
    float length;
    // point3 hit;
    // double psi; // the incident angle 
    // bool is_source;
};

class ray_data
{
    public:
        ray_data() {}
        // bounce_hist(point_bool hit_point) { add(hit_point); }

        void clear() { hit_data.clear(); }
        void add(float ray_length)
        {
            postp_data new_data;
            new_data.length = ray_length;
            hit_data.push_back(new_data); 
        }

    public:
        std::vector<postp_data> hit_data;
};

#endif