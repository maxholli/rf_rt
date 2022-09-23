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

hittable_list floating_square() 
{
    hittable_list world;
    auto material_s1 = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    // world.add(make_shared<xy_rect>(-1, 1, 1, 3, -5, material_s1));
    point3 a = point3(-1, 1, -5);
    point3 b = point3(1, 1, -5);
    point3 c = point3(-1, 3, -5);
    world.add(make_shared<triangle>(c, b, a, material_s1));
    a = point3(-1, 1, -5);
    world.add(make_shared<triangle>(c, b, a, material_s1));
    return world;
}