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

hittable_list ground_only(double recv_center_z, double rad_sphere, double recv_height) 
{
    hittable_list world;

    // make receiver sphere
    // Floating receiver at location (0,recv_height,recv_center_z)
    auto material_rx_tower = make_shared<rf_transmit>(color(1, 1, 1));
    world.add(make_shared<sphere>(point3( 0, recv_height, recv_center_z), rad_sphere, material_rx_tower));

    // make ground
    // currently the ground reflects in a specular fashion (rf_universal)
    // no effective roughness
    auto material_ground = make_shared<rf_universal>(color(15.0, 12e-3, 1.0));
    point3 a = point3(-2000, 0, -2000);
    point3 b = point3(2000, 0, -2000);
    point3 c = point3(-2000, 0, 2000);
    world.add(make_shared<triangle>(a, c, b, material_ground));
    a = point3(2000, 0, 2000);
    world.add(make_shared<triangle>(c, a, b, material_ground));
    return world;
}