#include "../headers/rtweekend.h"
#include "../headers/color.h"
#include "../headers/hittable_list.h"
#include "../headers/sphere.h"
#include "../headers/camera.h"
#include "../headers/material.h"
// #include "../headers/aarect.h"
// #include "../headers/box.h"
#include "../headers/bounce_hist.h"
#include "../headers/triangle.h"

hittable_list floating_triangle() 
{
    hittable_list world;
    auto material_s1 = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    point3 a = point3(0, 6, -4);
    point3 b = point3(-4, 1, -4);
    point3 c = point3(6, 2, -4);
    world.add(make_shared<triangle>(c, b, a, material_s1));
    return world;
}
