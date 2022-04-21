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

hittable_list empty() 
{
    hittable_list world;

    // Floating transmitter at location 10,10,10
    double radius_of_sphere = 0.564189584;
    auto material_tx_tower = make_shared<rf_transmit>(color(4, 4, 4));
    world.add(make_shared<sphere>(point3( 0, 0, 500), radius_of_sphere, material_tx_tower));

    return world;
}