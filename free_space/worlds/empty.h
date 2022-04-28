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

hittable_list empty(double recv_center_z, double rad_sphere) 
{
    hittable_list world;

    // Floating receiver at location (0,0,recv_center_z)
    auto material_tx_tower = make_shared<rf_transmit>(color(4, 4, 4));
    world.add(make_shared<sphere>(point3( 0, 0, recv_center_z), rad_sphere, material_tx_tower));

    return world;
}