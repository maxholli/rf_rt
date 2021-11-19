#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class sphere : public hittable
{
    public:
        sphere() {}
        sphere(point3 cen, double r, shared_ptr<material> m)
         : center(cen), radius(r), mat_ptr(m) {};

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    // A is the origin of ray.
    // b is the direction or ray.
    // C is the center point.
    // r is the radius.
    // discriminant = (2*b.(A-C))^2 - 4*b.b*((A-C).(A-C)-r^2)
    
    vec3 oc = r.origin() - center;
    //double b = 2.0 * dot(r.direction(), r.origin()-center);
    double half_b = dot(oc, r.direction());
    // double a = dot(r.direction(), r.direction());
    double a = r.direction().length_squared(); 
    // double c = dot(r.origin()-center, r.origin()-center) - radius*radius;
    double c = oc.length_squared() - radius*radius;
    //double discriminant = b*b - 4 * a * c;
    double discriminant = half_b*half_b - a * c;

    if (discriminant < 0)
    {
        return false;
    }
    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || root > t_max)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max)
        {
            return false;
        }
    }
    rec.t = root;
    rec.p = r.at(root);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    
    return true;
}

#endif