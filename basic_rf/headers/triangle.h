#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "rtweekend.h"
#include "hittable.h"
#include "vec3.h"

class triangle : public hittable
{
    public:
        triangle() {}

        triangle(point3 _a, point3 _b, point3 _c,
            shared_ptr<material> mat)
            : a(_a), b(_b), c(_c), mp(mat) {
                n = unit_vector(cross(a-b, a-c));
                D = -1*n.x()*a.x() - n.y()*a.y() - n.z()*a.z(); // using a is arbitrary (i think) could us b or c
            }; 

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

    public:
        point3 a;
        point3 b;
        point3 c;
        shared_ptr<material> mp;
        vec3 n; // surface normal
        double D; // from the trianlge's plane equation Ax + By + Cz + D = 0
};

bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    // double t = (k-r.origin().z()) / r.direction().z();
    // double t = 10.0; // i think you need to know the hit point first before you can find t
    double denom = dot(n, r.dir);
    if (denom == 0) 
        return false;
    double t = -1 * (dot(n, r.orig) + D) / denom;
    if (t < t_min || t > t_max)
        return false;
    point3 p_hit = r.at(t);

    vec3 tester;

    tester = cross(b - a, p_hit - a); // WARNING: order could matter here
    if (dot(n, tester) < 0)
        return false;

    tester = cross(c - b, p_hit - b); // WARNING: order could matter here
    if (dot(n, tester) < 0)
        return false;

    tester = cross(a - c, p_hit - c); // WARNING: order could matter here
    if (dot(n, tester) < 0)
        return false;    

    rec.t = t;
    // auto outward_normal = vec3(0, 0, 1);
    rec.set_face_normal(r, n);
    rec.mat_ptr = mp;
    rec.p = p_hit;
    return true; 
}

bool triangle::bounding_box(double time0, double time1, aabb& output_box) const
{
    vec3 padding(0.0001, 0.0001, 0.0001);
    double x_min = fmin(fmin(a.x(), b.x()), c.x());
    double y_min = fmin(fmin(a.y(), b.y()), c.y());
    double z_min = fmin(fmin(a.z(), b.z()), c.z());

    double x_max = fmax(fmax(a.x(), b.x()), c.x());
    double y_max = fmax(fmax(a.y(), b.y()), c.y());
    double z_max = fmax(fmax(a.z(), b.z()), c.z());
    
    output_box = aabb(
        vec3(x_min, y_min, z_min) - padding,
        vec3(x_max, y_max, z_max) + padding);
    return true;
}


#endif