#ifndef BOUNCE_HIST_H
#define BOUNCE_HIST_H

#include "hittable.h"
#include "vec3.h"

#include <vector>
#include <memory>

using std::shared_ptr;

struct point_bool {
    point3 hit;
    bool is_source;
};

class bounce_hist
{
    public:
        bounce_hist() {}
        // bounce_hist(point_bool hit_point) { add(hit_point); }

        void clear() { hit_points.clear(); }
        void add(point3 hit_point, bool is_s)
        {
            point_bool new_point;
            new_point.hit = hit_point;
            new_point.is_source = is_s;
            hit_points.push_back(new_point); 
        }

    public:
        std::vector<point_bool> hit_points;
};


// class bounce_hist
// {
//     public:
//         bounce_hist() {}
//         bounce_hist(shared_ptr<hit_record> hit_point) { add(hit_point); }

//         void clear() { hit_points.clear(); }
//         void add(shared_ptr<hit_record> hit_point) { hit_points.push_back(hit_point); }

//     public:
//         std::vector<shared_ptr<hit_record>> hit_points;
// };

#endif