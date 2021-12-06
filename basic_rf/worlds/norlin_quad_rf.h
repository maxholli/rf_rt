#include "../headers/rtweekend.h"
#include "../headers/color.h"
#include "../headers/hittable_list.h"
#include "../headers/sphere.h"
#include "../headers/camera.h"
#include "../headers/material.h"
#include "../headers/aarect.h"
#include "../headers/box.h"
#include "../headers/bounce_hist.h"
#include "../headers/triangle.h"

hittable_list norlin_quad_rf()
{
    hittable_list world;
    auto material_s1 = make_shared<rf_universal>(color(0.7, 0.3, 0.3));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto tx_tower = make_shared<rf_transmit>(color(4, 4, 4));

    // b_336137
    world.add(make_shared<triangle>(point3(108.48,0.00,-333.12), point3(108.48,0.00,-337.70), point3(108.48,20.00,-333.12), material_s1));
    world.add(make_shared<triangle>(point3(108.48,0.00,-337.70), point3(115.63,0.00,-337.70), point3(108.48,20.00,-337.70), material_s1));
    world.add(make_shared<triangle>(point3(115.63,0.00,-337.70), point3(115.63,0.00,-332.89), point3(115.63,20.00,-337.70), material_s1));
    world.add(make_shared<triangle>(point3(115.63,0.00,-332.89), point3(143.78,0.00,-333.00), point3(115.63,20.00,-332.89), material_s1));
    world.add(make_shared<triangle>(point3(143.78,0.00,-333.00), point3(143.87,0.00,-315.79), point3(143.78,20.00,-333.00), material_s1));
    world.add(make_shared<triangle>(point3(143.87,0.00,-315.79), point3(80.59,0.00,-315.57), point3(143.87,20.00,-315.79), material_s1));
    world.add(make_shared<triangle>(point3(80.59,0.00,-315.57), point3(80.59,0.00,-333.00), point3(80.59,20.00,-315.57), material_s1));
    world.add(make_shared<triangle>(point3(80.59,0.00,-333.00), point3(108.48,0.00,-333.12), point3(80.59,20.00,-333.00), material_s1));
    world.add(make_shared<triangle>(point3(108.48,20.00,-333.12), point3(108.48,20.00,-337.70), point3(108.48,0.00,-337.70), material_s1));
    world.add(make_shared<triangle>(point3(108.48,20.00,-337.70), point3(115.63,20.00,-337.70), point3(115.63,0.00,-337.70), material_s1));
    world.add(make_shared<triangle>(point3(115.63,20.00,-337.70), point3(115.63,20.00,-332.89), point3(115.63,0.00,-332.89), material_s1));
    world.add(make_shared<triangle>(point3(115.63,20.00,-332.89), point3(143.78,20.00,-333.00), point3(143.78,0.00,-333.00), material_s1));
    world.add(make_shared<triangle>(point3(143.78,20.00,-333.00), point3(143.87,20.00,-315.79), point3(143.87,0.00,-315.79), material_s1));
    world.add(make_shared<triangle>(point3(143.87,20.00,-315.79), point3(80.59,20.00,-315.57), point3(80.59,0.00,-315.57), material_s1));
    world.add(make_shared<triangle>(point3(80.59,20.00,-315.57), point3(80.59,20.00,-333.00), point3(80.59,0.00,-333.00), material_s1));
    world.add(make_shared<triangle>(point3(80.59,20.00,-333.00), point3(108.48,20.00,-333.12), point3(108.48,0.00,-333.12), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(133.80,0.00,-203.71), point3(122.00,0.00,-197.67), point3(133.80,20.00,-203.71), material_s1));
    world.add(make_shared<triangle>(point3(122.00,0.00,-197.67), point3(112.87,0.00,-215.44), point3(122.00,20.00,-197.67), material_s1));
    world.add(make_shared<triangle>(point3(112.87,0.00,-215.44), point3(124.67,0.00,-221.48), point3(112.87,20.00,-215.44), material_s1));
    world.add(make_shared<triangle>(point3(124.67,0.00,-221.48), point3(133.80,0.00,-203.71), point3(124.67,20.00,-221.48), material_s1));
    world.add(make_shared<triangle>(point3(133.80,20.00,-203.71), point3(122.00,20.00,-197.67), point3(122.00,0.00,-197.67), material_s1));
    world.add(make_shared<triangle>(point3(122.00,20.00,-197.67), point3(112.87,20.00,-215.44), point3(112.87,0.00,-215.44), material_s1));
    world.add(make_shared<triangle>(point3(112.87,20.00,-215.44), point3(124.67,20.00,-221.48), point3(124.67,0.00,-221.48), material_s1));
    world.add(make_shared<triangle>(point3(124.67,20.00,-221.48), point3(133.80,20.00,-203.71), point3(133.80,0.00,-203.71), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(193.20,0.00,-200.13), point3(156.01,0.00,-199.91), point3(193.20,20.00,-200.13), material_s1));
    world.add(make_shared<triangle>(point3(156.01,0.00,-199.91), point3(156.01,0.00,-217.68), point3(156.01,20.00,-199.91), material_s1));
    world.add(make_shared<triangle>(point3(156.01,0.00,-217.68), point3(169.01,0.00,-217.68), point3(156.01,20.00,-217.68), material_s1));
    world.add(make_shared<triangle>(point3(169.01,0.00,-217.68), point3(169.01,0.00,-221.03), point3(169.01,20.00,-217.68), material_s1));
    world.add(make_shared<triangle>(point3(169.01,0.00,-221.03), point3(180.89,0.00,-221.03), point3(169.01,20.00,-221.03), material_s1));
    world.add(make_shared<triangle>(point3(180.89,0.00,-221.03), point3(180.89,0.00,-217.90), point3(180.89,20.00,-221.03), material_s1));
    world.add(make_shared<triangle>(point3(180.89,0.00,-217.90), point3(193.12,0.00,-217.90), point3(180.89,20.00,-217.90), material_s1));
    world.add(make_shared<triangle>(point3(193.12,0.00,-217.90), point3(193.20,0.00,-200.13), point3(193.12,20.00,-217.90), material_s1));
    world.add(make_shared<triangle>(point3(193.20,20.00,-200.13), point3(156.01,20.00,-199.91), point3(156.01,0.00,-199.91), material_s1));
    world.add(make_shared<triangle>(point3(156.01,20.00,-199.91), point3(156.01,20.00,-217.68), point3(156.01,0.00,-217.68), material_s1));
    world.add(make_shared<triangle>(point3(156.01,20.00,-217.68), point3(169.01,20.00,-217.68), point3(169.01,0.00,-217.68), material_s1));
    world.add(make_shared<triangle>(point3(169.01,20.00,-217.68), point3(169.01,20.00,-221.03), point3(169.01,0.00,-221.03), material_s1));
    world.add(make_shared<triangle>(point3(169.01,20.00,-221.03), point3(180.89,20.00,-221.03), point3(180.89,0.00,-221.03), material_s1));
    world.add(make_shared<triangle>(point3(180.89,20.00,-221.03), point3(180.89,20.00,-217.90), point3(180.89,0.00,-217.90), material_s1));
    world.add(make_shared<triangle>(point3(180.89,20.00,-217.90), point3(193.12,20.00,-217.90), point3(193.12,0.00,-217.90), material_s1));
    world.add(make_shared<triangle>(point3(193.12,20.00,-217.90), point3(193.20,20.00,-200.13), point3(193.20,0.00,-200.13), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(199.06,0.00,-219.24), point3(238.32,0.00,-218.01), point3(199.06,20.00,-219.24), material_s1));
    world.add(make_shared<triangle>(point3(238.32,0.00,-218.01), point3(238.41,0.00,-221.25), point3(238.32,20.00,-218.01), material_s1));
    world.add(make_shared<triangle>(point3(238.41,0.00,-221.25), point3(259.07,0.00,-220.58), point3(238.41,20.00,-221.25), material_s1));
    world.add(make_shared<triangle>(point3(259.07,0.00,-220.58), point3(258.98,0.00,-218.35), point3(259.07,20.00,-220.58), material_s1));
    world.add(make_shared<triangle>(point3(258.98,0.00,-218.35), point3(263.72,0.00,-218.23), point3(258.98,20.00,-218.35), material_s1));
    world.add(make_shared<triangle>(point3(263.72,0.00,-218.23), point3(263.46,0.00,-209.85), point3(263.72,20.00,-218.23), material_s1));
    world.add(make_shared<triangle>(point3(263.46,0.00,-209.85), point3(259.24,0.00,-210.08), point3(263.46,20.00,-209.85), material_s1));
    world.add(make_shared<triangle>(point3(259.24,0.00,-210.08), point3(258.81,0.00,-199.01), point3(259.24,20.00,-210.08), material_s1));
    world.add(make_shared<triangle>(point3(258.81,0.00,-199.01), point3(265.79,0.00,-198.79), point3(258.81,20.00,-199.01), material_s1));
    world.add(make_shared<triangle>(point3(265.79,0.00,-198.79), point3(265.27,0.00,-181.80), point3(265.79,20.00,-198.79), material_s1));
    world.add(make_shared<triangle>(point3(265.27,0.00,-181.80), point3(255.88,0.00,-182.14), point3(265.27,20.00,-181.80), material_s1));
    world.add(make_shared<triangle>(point3(255.88,0.00,-182.14), point3(255.80,0.00,-178.45), point3(255.88,20.00,-182.14), material_s1));
    world.add(make_shared<triangle>(point3(255.80,0.00,-178.45), point3(231.35,0.00,-179.23), point3(255.80,20.00,-178.45), material_s1));
    world.add(make_shared<triangle>(point3(231.35,0.00,-179.23), point3(231.86,0.00,-195.33), point3(231.35,20.00,-179.23), material_s1));
    world.add(make_shared<triangle>(point3(231.86,0.00,-195.33), point3(210.17,0.00,-196.00), point3(231.86,20.00,-195.33), material_s1));
    world.add(make_shared<triangle>(point3(210.17,0.00,-196.00), point3(209.91,0.00,-187.73), point3(210.17,20.00,-196.00), material_s1));
    world.add(make_shared<triangle>(point3(209.91,0.00,-187.73), point3(198.11,0.00,-188.06), point3(209.91,20.00,-187.73), material_s1));
    world.add(make_shared<triangle>(point3(198.11,0.00,-188.06), point3(199.06,0.00,-219.24), point3(198.11,20.00,-188.06), material_s1));
    world.add(make_shared<triangle>(point3(199.06,20.00,-219.24), point3(238.32,20.00,-218.01), point3(238.32,0.00,-218.01), material_s1));
    world.add(make_shared<triangle>(point3(238.32,20.00,-218.01), point3(238.41,20.00,-221.25), point3(238.41,0.00,-221.25), material_s1));
    world.add(make_shared<triangle>(point3(238.41,20.00,-221.25), point3(259.07,20.00,-220.58), point3(259.07,0.00,-220.58), material_s1));
    world.add(make_shared<triangle>(point3(259.07,20.00,-220.58), point3(258.98,20.00,-218.35), point3(258.98,0.00,-218.35), material_s1));
    world.add(make_shared<triangle>(point3(258.98,20.00,-218.35), point3(263.72,20.00,-218.23), point3(263.72,0.00,-218.23), material_s1));
    world.add(make_shared<triangle>(point3(263.72,20.00,-218.23), point3(263.46,20.00,-209.85), point3(263.46,0.00,-209.85), material_s1));
    world.add(make_shared<triangle>(point3(263.46,20.00,-209.85), point3(259.24,20.00,-210.08), point3(259.24,0.00,-210.08), material_s1));
    world.add(make_shared<triangle>(point3(259.24,20.00,-210.08), point3(258.81,20.00,-199.01), point3(258.81,0.00,-199.01), material_s1));
    world.add(make_shared<triangle>(point3(258.81,20.00,-199.01), point3(265.79,20.00,-198.79), point3(265.79,0.00,-198.79), material_s1));
    world.add(make_shared<triangle>(point3(265.79,20.00,-198.79), point3(265.27,20.00,-181.80), point3(265.27,0.00,-181.80), material_s1));
    world.add(make_shared<triangle>(point3(265.27,20.00,-181.80), point3(255.88,20.00,-182.14), point3(255.88,0.00,-182.14), material_s1));
    world.add(make_shared<triangle>(point3(255.88,20.00,-182.14), point3(255.80,20.00,-178.45), point3(255.80,0.00,-178.45), material_s1));
    world.add(make_shared<triangle>(point3(255.80,20.00,-178.45), point3(231.35,20.00,-179.23), point3(231.35,0.00,-179.23), material_s1));
    world.add(make_shared<triangle>(point3(231.35,20.00,-179.23), point3(231.86,20.00,-195.33), point3(231.86,0.00,-195.33), material_s1));
    world.add(make_shared<triangle>(point3(231.86,20.00,-195.33), point3(210.17,20.00,-196.00), point3(210.17,0.00,-196.00), material_s1));
    world.add(make_shared<triangle>(point3(210.17,20.00,-196.00), point3(209.91,20.00,-187.73), point3(209.91,0.00,-187.73), material_s1));
    world.add(make_shared<triangle>(point3(209.91,20.00,-187.73), point3(198.11,20.00,-188.06), point3(198.11,0.00,-188.06), material_s1));
    world.add(make_shared<triangle>(point3(198.11,20.00,-188.06), point3(199.06,20.00,-219.24), point3(199.06,0.00,-219.24), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(233.59,0.00,-335.57), point3(241.33,0.00,-335.35), point3(233.59,20.00,-335.57), material_s1));
    world.add(make_shared<triangle>(point3(241.33,0.00,-335.35), point3(241.51,0.00,-339.04), point3(241.33,20.00,-335.35), material_s1));
    world.add(make_shared<triangle>(point3(241.51,0.00,-339.04), point3(253.13,0.00,-338.70), point3(241.51,20.00,-339.04), material_s1));
    world.add(make_shared<triangle>(point3(253.13,0.00,-338.70), point3(253.04,0.00,-337.59), point3(253.13,20.00,-338.70), material_s1));
    world.add(make_shared<triangle>(point3(253.04,0.00,-337.59), point3(258.81,0.00,-337.47), point3(253.04,20.00,-337.59), material_s1));
    world.add(make_shared<triangle>(point3(258.81,0.00,-337.47), point3(258.81,0.00,-335.46), point3(258.81,20.00,-337.47), material_s1));
    world.add(make_shared<triangle>(point3(258.81,0.00,-335.46), point3(265.01,0.00,-335.35), point3(258.81,20.00,-335.46), material_s1));
    world.add(make_shared<triangle>(point3(265.01,0.00,-335.35), point3(264.75,0.00,-328.42), point3(265.01,20.00,-335.35), material_s1));
    world.add(make_shared<triangle>(point3(264.75,0.00,-328.42), point3(268.71,0.00,-328.31), point3(264.75,20.00,-328.42), material_s1));
    world.add(make_shared<triangle>(point3(268.71,0.00,-328.31), point3(268.28,0.00,-315.68), point3(268.71,20.00,-328.31), material_s1));
    world.add(make_shared<triangle>(point3(268.28,0.00,-315.68), point3(248.82,0.00,-316.24), point3(268.28,20.00,-315.68), material_s1));
    world.add(make_shared<triangle>(point3(248.82,0.00,-316.24), point3(248.91,0.00,-317.69), point3(248.82,20.00,-316.24), material_s1));
    world.add(make_shared<triangle>(point3(248.91,0.00,-317.69), point3(233.07,0.00,-318.14), point3(248.91,20.00,-317.69), material_s1));
    world.add(make_shared<triangle>(point3(233.07,0.00,-318.14), point3(233.59,0.00,-335.57), point3(233.07,20.00,-318.14), material_s1));
    world.add(make_shared<triangle>(point3(233.59,20.00,-335.57), point3(241.33,20.00,-335.35), point3(241.33,0.00,-335.35), material_s1));
    world.add(make_shared<triangle>(point3(241.33,20.00,-335.35), point3(241.51,20.00,-339.04), point3(241.51,0.00,-339.04), material_s1));
    world.add(make_shared<triangle>(point3(241.51,20.00,-339.04), point3(253.13,20.00,-338.70), point3(253.13,0.00,-338.70), material_s1));
    world.add(make_shared<triangle>(point3(253.13,20.00,-338.70), point3(253.04,20.00,-337.59), point3(253.04,0.00,-337.59), material_s1));
    world.add(make_shared<triangle>(point3(253.04,20.00,-337.59), point3(258.81,20.00,-337.47), point3(258.81,0.00,-337.47), material_s1));
    world.add(make_shared<triangle>(point3(258.81,20.00,-337.47), point3(258.81,20.00,-335.46), point3(258.81,0.00,-335.46), material_s1));
    world.add(make_shared<triangle>(point3(258.81,20.00,-335.46), point3(265.01,20.00,-335.35), point3(265.01,0.00,-335.35), material_s1));
    world.add(make_shared<triangle>(point3(265.01,20.00,-335.35), point3(264.75,20.00,-328.42), point3(264.75,0.00,-328.42), material_s1));
    world.add(make_shared<triangle>(point3(264.75,20.00,-328.42), point3(268.71,20.00,-328.31), point3(268.71,0.00,-328.31), material_s1));
    world.add(make_shared<triangle>(point3(268.71,20.00,-328.31), point3(268.28,20.00,-315.68), point3(268.28,0.00,-315.68), material_s1));
    world.add(make_shared<triangle>(point3(268.28,20.00,-315.68), point3(248.82,20.00,-316.24), point3(248.82,0.00,-316.24), material_s1));
    world.add(make_shared<triangle>(point3(248.82,20.00,-316.24), point3(248.91,20.00,-317.69), point3(248.91,0.00,-317.69), material_s1));
    world.add(make_shared<triangle>(point3(248.91,20.00,-317.69), point3(233.07,20.00,-318.14), point3(233.07,0.00,-318.14), material_s1));
    world.add(make_shared<triangle>(point3(233.07,20.00,-318.14), point3(233.59,20.00,-335.57), point3(233.59,0.00,-335.57), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(422.66,0.00,-149.84), point3(499.55,0.00,-179.79), point3(422.66,20.00,-149.84), material_s1));
    world.add(make_shared<triangle>(point3(499.55,0.00,-179.79), point3(522.79,0.00,-120.56), point3(499.55,20.00,-179.79), material_s1));
    world.add(make_shared<triangle>(point3(522.79,0.00,-120.56), point3(533.73,0.00,-130.06), point3(522.79,20.00,-120.56), material_s1));
    world.add(make_shared<triangle>(point3(533.73,0.00,-130.06), point3(518.58,0.00,-168.50), point3(533.73,20.00,-130.06), material_s1));
    world.add(make_shared<triangle>(point3(518.58,0.00,-168.50), point3(564.72,0.00,-166.27), point3(518.58,20.00,-168.50), material_s1));
    world.add(make_shared<triangle>(point3(564.72,0.00,-166.27), point3(561.19,0.00,-93.63), point3(564.72,20.00,-166.27), material_s1));
    world.add(make_shared<triangle>(point3(561.19,0.00,-93.63), point3(530.54,0.00,-95.08), point3(561.19,20.00,-93.63), material_s1));
    world.add(make_shared<triangle>(point3(530.54,0.00,-95.08), point3(523.74,0.00,-112.29), point3(530.54,20.00,-95.08), material_s1));
    world.add(make_shared<triangle>(point3(523.74,0.00,-112.29), point3(477.76,0.00,-94.41), point3(523.74,20.00,-112.29), material_s1));
    world.add(make_shared<triangle>(point3(477.76,0.00,-94.41), point3(445.73,0.00,-80.00), point3(477.76,20.00,-94.41), material_s1));
    world.add(make_shared<triangle>(point3(445.73,0.00,-80.00), point3(448.15,0.00,-73.85), point3(445.73,20.00,-80.00), material_s1));
    world.add(make_shared<triangle>(point3(448.15,0.00,-73.85), point3(458.48,0.00,-82.79), point3(448.15,20.00,-73.85), material_s1));
    world.add(make_shared<triangle>(point3(458.48,0.00,-82.79), point3(455.55,0.00,-22.11), point3(458.48,20.00,-82.79), material_s1));
    world.add(make_shared<triangle>(point3(455.55,0.00,-22.11), point3(406.56,0.00,-3.00), point3(455.55,20.00,-22.11), material_s1));
    world.add(make_shared<triangle>(point3(406.56,0.00,-3.00), point3(407.68,0.00,-25.13), point3(406.56,20.00,-3.00), material_s1));
    world.add(make_shared<triangle>(point3(407.68,0.00,-25.13), point3(380.13,0.00,-26.36), point3(407.68,20.00,-25.13), material_s1));
    world.add(make_shared<triangle>(point3(380.13,0.00,-26.36), point3(378.84,0.00,0.35), point3(380.13,20.00,-26.36), material_s1));
    world.add(make_shared<triangle>(point3(378.84,0.00,0.35), point3(357.22,0.00,-0.65), point3(378.84,20.00,0.35), material_s1));
    world.add(make_shared<triangle>(point3(357.22,0.00,-0.65), point3(361.87,0.00,-95.19), point3(357.22,20.00,-0.65), material_s1));
    world.add(make_shared<triangle>(point3(361.87,0.00,-95.19), point3(426.62,0.00,-92.07), point3(361.87,20.00,-95.19), material_s1));
    world.add(make_shared<triangle>(point3(426.62,0.00,-92.07), point3(428.60,0.00,-132.19), point3(426.62,20.00,-92.07), material_s1));
    world.add(make_shared<triangle>(point3(428.60,0.00,-132.19), point3(361.62,0.00,-143.70), point3(428.60,20.00,-132.19), material_s1));
    world.add(make_shared<triangle>(point3(361.62,0.00,-143.70), point3(362.39,0.00,-159.23), point3(361.62,20.00,-143.70), material_s1));
    world.add(make_shared<triangle>(point3(362.39,0.00,-159.23), point3(404.32,0.00,-157.22), point3(362.39,20.00,-159.23), material_s1));
    world.add(make_shared<triangle>(point3(404.32,0.00,-157.22), point3(404.84,0.00,-168.28), point3(404.32,20.00,-157.22), material_s1));
    world.add(make_shared<triangle>(point3(404.84,0.00,-168.28), point3(346.29,0.00,-190.30), point3(404.84,20.00,-168.28), material_s1));
    world.add(make_shared<triangle>(point3(346.29,0.00,-190.30), point3(348.27,0.00,-229.52), point3(346.29,20.00,-190.30), material_s1));
    world.add(make_shared<triangle>(point3(348.27,0.00,-229.52), point3(426.36,0.00,-225.72), point3(348.27,20.00,-229.52), material_s1));
    world.add(make_shared<triangle>(point3(426.36,0.00,-225.72), point3(422.66,0.00,-149.84), point3(426.36,20.00,-225.72), material_s1));
    world.add(make_shared<triangle>(point3(422.66,20.00,-149.84), point3(499.55,20.00,-179.79), point3(499.55,0.00,-179.79), material_s1));
    world.add(make_shared<triangle>(point3(499.55,20.00,-179.79), point3(522.79,20.00,-120.56), point3(522.79,0.00,-120.56), material_s1));
    world.add(make_shared<triangle>(point3(522.79,20.00,-120.56), point3(533.73,20.00,-130.06), point3(533.73,0.00,-130.06), material_s1));
    world.add(make_shared<triangle>(point3(533.73,20.00,-130.06), point3(518.58,20.00,-168.50), point3(518.58,0.00,-168.50), material_s1));
    world.add(make_shared<triangle>(point3(518.58,20.00,-168.50), point3(564.72,20.00,-166.27), point3(564.72,0.00,-166.27), material_s1));
    world.add(make_shared<triangle>(point3(564.72,20.00,-166.27), point3(561.19,20.00,-93.63), point3(561.19,0.00,-93.63), material_s1));
    world.add(make_shared<triangle>(point3(561.19,20.00,-93.63), point3(530.54,20.00,-95.08), point3(530.54,0.00,-95.08), material_s1));
    world.add(make_shared<triangle>(point3(530.54,20.00,-95.08), point3(523.74,20.00,-112.29), point3(523.74,0.00,-112.29), material_s1));
    world.add(make_shared<triangle>(point3(523.74,20.00,-112.29), point3(477.76,20.00,-94.41), point3(477.76,0.00,-94.41), material_s1));
    world.add(make_shared<triangle>(point3(477.76,20.00,-94.41), point3(445.73,20.00,-80.00), point3(445.73,0.00,-80.00), material_s1));
    world.add(make_shared<triangle>(point3(445.73,20.00,-80.00), point3(448.15,20.00,-73.85), point3(448.15,0.00,-73.85), material_s1));
    world.add(make_shared<triangle>(point3(448.15,20.00,-73.85), point3(458.48,20.00,-82.79), point3(458.48,0.00,-82.79), material_s1));
    world.add(make_shared<triangle>(point3(458.48,20.00,-82.79), point3(455.55,20.00,-22.11), point3(455.55,0.00,-22.11), material_s1));
    world.add(make_shared<triangle>(point3(455.55,20.00,-22.11), point3(406.56,20.00,-3.00), point3(406.56,0.00,-3.00), material_s1));
    world.add(make_shared<triangle>(point3(406.56,20.00,-3.00), point3(407.68,20.00,-25.13), point3(407.68,0.00,-25.13), material_s1));
    world.add(make_shared<triangle>(point3(407.68,20.00,-25.13), point3(380.13,20.00,-26.36), point3(380.13,0.00,-26.36), material_s1));
    world.add(make_shared<triangle>(point3(380.13,20.00,-26.36), point3(378.84,20.00,0.35), point3(378.84,0.00,0.35), material_s1));
    world.add(make_shared<triangle>(point3(378.84,20.00,0.35), point3(357.22,20.00,-0.65), point3(357.22,0.00,-0.65), material_s1));
    world.add(make_shared<triangle>(point3(357.22,20.00,-0.65), point3(361.87,20.00,-95.19), point3(361.87,0.00,-95.19), material_s1));
    world.add(make_shared<triangle>(point3(361.87,20.00,-95.19), point3(426.62,20.00,-92.07), point3(426.62,0.00,-92.07), material_s1));
    world.add(make_shared<triangle>(point3(426.62,20.00,-92.07), point3(428.60,20.00,-132.19), point3(428.60,0.00,-132.19), material_s1));
    world.add(make_shared<triangle>(point3(428.60,20.00,-132.19), point3(361.62,20.00,-143.70), point3(361.62,0.00,-143.70), material_s1));
    world.add(make_shared<triangle>(point3(361.62,20.00,-143.70), point3(362.39,20.00,-159.23), point3(362.39,0.00,-159.23), material_s1));
    world.add(make_shared<triangle>(point3(362.39,20.00,-159.23), point3(404.32,20.00,-157.22), point3(404.32,0.00,-157.22), material_s1));
    world.add(make_shared<triangle>(point3(404.32,20.00,-157.22), point3(404.84,20.00,-168.28), point3(404.84,0.00,-168.28), material_s1));
    world.add(make_shared<triangle>(point3(404.84,20.00,-168.28), point3(346.29,20.00,-190.30), point3(346.29,0.00,-190.30), material_s1));
    world.add(make_shared<triangle>(point3(346.29,20.00,-190.30), point3(348.27,20.00,-229.52), point3(348.27,0.00,-229.52), material_s1));
    world.add(make_shared<triangle>(point3(348.27,20.00,-229.52), point3(426.36,20.00,-225.72), point3(426.36,0.00,-225.72), material_s1));
    world.add(make_shared<triangle>(point3(426.36,20.00,-225.72), point3(422.66,20.00,-149.84), point3(422.66,0.00,-149.84), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(326.06,0.00,-322.39), point3(326.06,0.00,-335.24), point3(326.06,20.00,-322.39), material_s1));
    world.add(make_shared<triangle>(point3(326.06,0.00,-335.24), point3(353.35,0.00,-335.24), point3(326.06,20.00,-335.24), material_s1));
    world.add(make_shared<triangle>(point3(353.35,0.00,-335.24), point3(353.35,0.00,-322.39), point3(353.35,20.00,-335.24), material_s1));
    world.add(make_shared<triangle>(point3(353.35,0.00,-322.39), point3(326.06,0.00,-322.39), point3(353.35,20.00,-322.39), material_s1));
    world.add(make_shared<triangle>(point3(326.06,20.00,-322.39), point3(326.06,20.00,-335.24), point3(326.06,0.00,-335.24), material_s1));
    world.add(make_shared<triangle>(point3(326.06,20.00,-335.24), point3(353.35,20.00,-335.24), point3(353.35,0.00,-335.24), material_s1));
    world.add(make_shared<triangle>(point3(353.35,20.00,-335.24), point3(353.35,20.00,-322.39), point3(353.35,0.00,-322.39), material_s1));
    world.add(make_shared<triangle>(point3(353.35,20.00,-322.39), point3(326.06,20.00,-322.39), point3(326.06,0.00,-322.39), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(356.10,0.00,-338.70), point3(407.85,0.00,-338.48), point3(356.10,20.00,-338.70), material_s1));
    world.add(make_shared<triangle>(point3(407.85,0.00,-338.48), point3(407.85,0.00,-321.27), point3(407.85,20.00,-338.48), material_s1));
    world.add(make_shared<triangle>(point3(407.85,0.00,-321.27), point3(402.25,0.00,-321.27), point3(407.85,20.00,-321.27), material_s1));
    world.add(make_shared<triangle>(point3(402.25,0.00,-321.27), point3(402.25,0.00,-311.44), point3(402.25,20.00,-321.27), material_s1));
    world.add(make_shared<triangle>(point3(402.25,0.00,-311.44), point3(359.03,0.00,-311.55), point3(402.25,20.00,-311.44), material_s1));
    world.add(make_shared<triangle>(point3(359.03,0.00,-311.55), point3(359.12,0.00,-321.94), point3(359.03,20.00,-311.55), material_s1));
    world.add(make_shared<triangle>(point3(359.12,0.00,-321.94), point3(356.10,0.00,-321.94), point3(359.12,20.00,-321.94), material_s1));
    world.add(make_shared<triangle>(point3(356.10,0.00,-321.94), point3(356.10,0.00,-338.70), point3(356.10,20.00,-321.94), material_s1));
    world.add(make_shared<triangle>(point3(356.10,20.00,-338.70), point3(407.85,20.00,-338.48), point3(407.85,0.00,-338.48), material_s1));
    world.add(make_shared<triangle>(point3(407.85,20.00,-338.48), point3(407.85,20.00,-321.27), point3(407.85,0.00,-321.27), material_s1));
    world.add(make_shared<triangle>(point3(407.85,20.00,-321.27), point3(402.25,20.00,-321.27), point3(402.25,0.00,-321.27), material_s1));
    world.add(make_shared<triangle>(point3(402.25,20.00,-321.27), point3(402.25,20.00,-311.44), point3(402.25,0.00,-311.44), material_s1));
    world.add(make_shared<triangle>(point3(402.25,20.00,-311.44), point3(359.03,20.00,-311.55), point3(359.03,0.00,-311.55), material_s1));
    world.add(make_shared<triangle>(point3(359.03,20.00,-311.55), point3(359.12,20.00,-321.94), point3(359.12,0.00,-321.94), material_s1));
    world.add(make_shared<triangle>(point3(359.12,20.00,-321.94), point3(356.10,20.00,-321.94), point3(356.10,0.00,-321.94), material_s1));
    world.add(make_shared<triangle>(point3(356.10,20.00,-321.94), point3(356.10,20.00,-338.70), point3(356.10,0.00,-338.70), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(526.93,0.00,-314.12), point3(527.10,0.00,-273.22), point3(526.93,20.00,-314.12), material_s1));
    world.add(make_shared<triangle>(point3(527.10,0.00,-273.22), point3(508.07,0.00,-273.11), point3(527.10,20.00,-273.22), material_s1));
    world.add(make_shared<triangle>(point3(508.07,0.00,-273.11), point3(508.24,0.00,-243.83), point3(508.07,20.00,-273.11), material_s1));
    world.add(make_shared<triangle>(point3(508.24,0.00,-243.83), point3(494.21,0.00,-243.71), point3(508.24,20.00,-243.83), material_s1));
    world.add(make_shared<triangle>(point3(494.21,0.00,-243.71), point3(494.21,0.00,-246.51), point3(494.21,20.00,-243.71), material_s1));
    world.add(make_shared<triangle>(point3(494.21,0.00,-246.51), point3(490.33,0.00,-246.51), point3(494.21,20.00,-246.51), material_s1));
    world.add(make_shared<triangle>(point3(490.33,0.00,-246.51), point3(490.42,0.00,-224.38), point3(490.33,20.00,-246.51), material_s1));
    world.add(make_shared<triangle>(point3(490.42,0.00,-224.38), point3(448.75,0.00,-224.16), point3(490.42,20.00,-224.38), material_s1));
    world.add(make_shared<triangle>(point3(448.75,0.00,-224.16), point3(448.75,0.00,-218.23), point3(448.75,20.00,-224.16), material_s1));
    world.add(make_shared<triangle>(point3(448.75,0.00,-218.23), point3(438.42,0.00,-218.12), point3(448.75,20.00,-218.23), material_s1));
    world.add(make_shared<triangle>(point3(438.42,0.00,-218.12), point3(438.33,0.00,-223.71), point3(438.42,20.00,-218.12), material_s1));
    world.add(make_shared<triangle>(point3(438.33,0.00,-223.71), point3(432.56,0.00,-223.71), point3(438.33,20.00,-223.71), material_s1));
    world.add(make_shared<triangle>(point3(432.56,0.00,-223.71), point3(432.39,0.00,-266.85), point3(432.56,20.00,-223.71), material_s1));
    world.add(make_shared<triangle>(point3(432.39,0.00,-266.85), point3(437.12,0.00,-266.96), point3(432.39,20.00,-266.85), material_s1));
    world.add(make_shared<triangle>(point3(437.12,0.00,-266.96), point3(437.04,0.00,-279.92), point3(437.12,20.00,-266.96), material_s1));
    world.add(make_shared<triangle>(point3(437.04,0.00,-279.92), point3(431.61,0.00,-279.92), point3(437.04,20.00,-279.92), material_s1));
    world.add(make_shared<triangle>(point3(431.61,0.00,-279.92), point3(431.44,0.00,-314.23), point3(431.61,20.00,-279.92), material_s1));
    world.add(make_shared<triangle>(point3(431.44,0.00,-314.23), point3(438.50,0.00,-314.23), point3(431.44,20.00,-314.23), material_s1));
    world.add(make_shared<triangle>(point3(438.50,0.00,-314.23), point3(438.50,0.00,-319.93), point3(438.50,20.00,-314.23), material_s1));
    world.add(make_shared<triangle>(point3(438.50,0.00,-319.93), point3(449.01,0.00,-320.04), point3(438.50,20.00,-319.93), material_s1));
    world.add(make_shared<triangle>(point3(449.01,0.00,-320.04), point3(449.01,0.00,-313.78), point3(449.01,20.00,-320.04), material_s1));
    world.add(make_shared<triangle>(point3(449.01,0.00,-313.78), point3(526.93,0.00,-314.12), point3(449.01,20.00,-313.78), material_s1));
    world.add(make_shared<triangle>(point3(526.93,20.00,-314.12), point3(527.10,20.00,-273.22), point3(527.10,0.00,-273.22), material_s1));
    world.add(make_shared<triangle>(point3(527.10,20.00,-273.22), point3(508.07,20.00,-273.11), point3(508.07,0.00,-273.11), material_s1));
    world.add(make_shared<triangle>(point3(508.07,20.00,-273.11), point3(508.24,20.00,-243.83), point3(508.24,0.00,-243.83), material_s1));
    world.add(make_shared<triangle>(point3(508.24,20.00,-243.83), point3(494.21,20.00,-243.71), point3(494.21,0.00,-243.71), material_s1));
    world.add(make_shared<triangle>(point3(494.21,20.00,-243.71), point3(494.21,20.00,-246.51), point3(494.21,0.00,-246.51), material_s1));
    world.add(make_shared<triangle>(point3(494.21,20.00,-246.51), point3(490.33,20.00,-246.51), point3(490.33,0.00,-246.51), material_s1));
    world.add(make_shared<triangle>(point3(490.33,20.00,-246.51), point3(490.42,20.00,-224.38), point3(490.42,0.00,-224.38), material_s1));
    world.add(make_shared<triangle>(point3(490.42,20.00,-224.38), point3(448.75,20.00,-224.16), point3(448.75,0.00,-224.16), material_s1));
    world.add(make_shared<triangle>(point3(448.75,20.00,-224.16), point3(448.75,20.00,-218.23), point3(448.75,0.00,-218.23), material_s1));
    world.add(make_shared<triangle>(point3(448.75,20.00,-218.23), point3(438.42,20.00,-218.12), point3(438.42,0.00,-218.12), material_s1));
    world.add(make_shared<triangle>(point3(438.42,20.00,-218.12), point3(438.33,20.00,-223.71), point3(438.33,0.00,-223.71), material_s1));
    world.add(make_shared<triangle>(point3(438.33,20.00,-223.71), point3(432.56,20.00,-223.71), point3(432.56,0.00,-223.71), material_s1));
    world.add(make_shared<triangle>(point3(432.56,20.00,-223.71), point3(432.39,20.00,-266.85), point3(432.39,0.00,-266.85), material_s1));
    world.add(make_shared<triangle>(point3(432.39,20.00,-266.85), point3(437.12,20.00,-266.96), point3(437.12,0.00,-266.96), material_s1));
    world.add(make_shared<triangle>(point3(437.12,20.00,-266.96), point3(437.04,20.00,-279.92), point3(437.04,0.00,-279.92), material_s1));
    world.add(make_shared<triangle>(point3(437.04,20.00,-279.92), point3(431.61,20.00,-279.92), point3(431.61,0.00,-279.92), material_s1));
    world.add(make_shared<triangle>(point3(431.61,20.00,-279.92), point3(431.44,20.00,-314.23), point3(431.44,0.00,-314.23), material_s1));
    world.add(make_shared<triangle>(point3(431.44,20.00,-314.23), point3(438.50,20.00,-314.23), point3(438.50,0.00,-314.23), material_s1));
    world.add(make_shared<triangle>(point3(438.50,20.00,-314.23), point3(438.50,20.00,-319.93), point3(438.50,0.00,-319.93), material_s1));
    world.add(make_shared<triangle>(point3(438.50,20.00,-319.93), point3(449.01,20.00,-320.04), point3(449.01,0.00,-320.04), material_s1));
    world.add(make_shared<triangle>(point3(449.01,20.00,-320.04), point3(449.01,20.00,-313.78), point3(449.01,0.00,-313.78), material_s1));
    world.add(make_shared<triangle>(point3(449.01,20.00,-313.78), point3(526.93,20.00,-314.12), point3(526.93,0.00,-314.12), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(139.39,0.00,-149.84), point3(139.65,0.00,-194.32), point3(139.39,20.00,-149.84), material_s1));
    world.add(make_shared<triangle>(point3(139.65,0.00,-194.32), point3(157.65,0.00,-194.32), point3(139.65,20.00,-194.32), material_s1));
    world.add(make_shared<triangle>(point3(157.65,0.00,-194.32), point3(157.65,0.00,-188.28), point3(157.65,20.00,-194.32), material_s1));
    world.add(make_shared<triangle>(point3(157.65,0.00,-188.28), point3(168.24,0.00,-188.28), point3(157.65,20.00,-188.28), material_s1));
    world.add(make_shared<triangle>(point3(168.24,0.00,-188.28), point3(168.24,0.00,-183.59), point3(168.24,20.00,-188.28), material_s1));
    world.add(make_shared<triangle>(point3(168.24,0.00,-183.59), point3(157.56,0.00,-183.59), point3(168.24,20.00,-183.59), material_s1));
    world.add(make_shared<triangle>(point3(157.56,0.00,-183.59), point3(157.39,0.00,-149.73), point3(157.56,20.00,-183.59), material_s1));
    world.add(make_shared<triangle>(point3(157.39,0.00,-149.73), point3(139.39,0.00,-149.84), point3(157.39,20.00,-149.73), material_s1));
    world.add(make_shared<triangle>(point3(139.39,20.00,-149.84), point3(139.65,20.00,-194.32), point3(139.65,0.00,-194.32), material_s1));
    world.add(make_shared<triangle>(point3(139.65,20.00,-194.32), point3(157.65,20.00,-194.32), point3(157.65,0.00,-194.32), material_s1));
    world.add(make_shared<triangle>(point3(157.65,20.00,-194.32), point3(157.65,20.00,-188.28), point3(157.65,0.00,-188.28), material_s1));
    world.add(make_shared<triangle>(point3(157.65,20.00,-188.28), point3(168.24,20.00,-188.28), point3(168.24,0.00,-188.28), material_s1));
    world.add(make_shared<triangle>(point3(168.24,20.00,-188.28), point3(168.24,20.00,-183.59), point3(168.24,0.00,-183.59), material_s1));
    world.add(make_shared<triangle>(point3(168.24,20.00,-183.59), point3(157.56,20.00,-183.59), point3(157.56,0.00,-183.59), material_s1));
    world.add(make_shared<triangle>(point3(157.56,20.00,-183.59), point3(157.39,20.00,-149.73), point3(157.39,0.00,-149.73), material_s1));
    world.add(make_shared<triangle>(point3(157.39,20.00,-149.73), point3(139.39,20.00,-149.84), point3(139.39,0.00,-149.84), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(168.41,0.00,-147.05), point3(191.40,0.00,-146.94), point3(168.41,20.00,-147.05), material_s1));
    world.add(make_shared<triangle>(point3(191.40,0.00,-146.94), point3(191.40,0.00,-159.34), point3(191.40,20.00,-146.94), material_s1));
    world.add(make_shared<triangle>(point3(191.40,0.00,-159.34), point3(201.13,0.00,-159.34), point3(191.40,20.00,-159.34), material_s1));
    world.add(make_shared<triangle>(point3(201.13,0.00,-159.34), point3(200.95,0.00,-108.61), point3(201.13,20.00,-159.34), material_s1));
    world.add(make_shared<triangle>(point3(200.95,0.00,-108.61), point3(191.48,0.00,-108.61), point3(200.95,20.00,-108.61), material_s1));
    world.add(make_shared<triangle>(point3(191.48,0.00,-108.61), point3(191.48,0.00,-120.90), point3(191.48,20.00,-108.61), material_s1));
    world.add(make_shared<triangle>(point3(191.48,0.00,-120.90), point3(168.32,0.00,-121.01), point3(191.48,20.00,-120.90), material_s1));
    world.add(make_shared<triangle>(point3(168.32,0.00,-121.01), point3(168.41,0.00,-147.05), point3(168.32,20.00,-121.01), material_s1));
    world.add(make_shared<triangle>(point3(168.41,20.00,-147.05), point3(191.40,20.00,-146.94), point3(191.40,0.00,-146.94), material_s1));
    world.add(make_shared<triangle>(point3(191.40,20.00,-146.94), point3(191.40,20.00,-159.34), point3(191.40,0.00,-159.34), material_s1));
    world.add(make_shared<triangle>(point3(191.40,20.00,-159.34), point3(201.13,20.00,-159.34), point3(201.13,0.00,-159.34), material_s1));
    world.add(make_shared<triangle>(point3(201.13,20.00,-159.34), point3(200.95,20.00,-108.61), point3(200.95,0.00,-108.61), material_s1));
    world.add(make_shared<triangle>(point3(200.95,20.00,-108.61), point3(191.48,20.00,-108.61), point3(191.48,0.00,-108.61), material_s1));
    world.add(make_shared<triangle>(point3(191.48,20.00,-108.61), point3(191.48,20.00,-120.90), point3(191.48,0.00,-120.90), material_s1));
    world.add(make_shared<triangle>(point3(191.48,20.00,-120.90), point3(168.32,20.00,-121.01), point3(168.32,0.00,-121.01), material_s1));
    world.add(make_shared<triangle>(point3(168.32,20.00,-121.01), point3(168.41,20.00,-147.05), point3(168.41,0.00,-147.05), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(339.06,0.00,-156.88), point3(338.11,0.00,-88.49), point3(339.06,20.00,-156.88), material_s1));
    world.add(make_shared<triangle>(point3(338.11,0.00,-88.49), point3(323.39,0.00,-88.60), point3(338.11,20.00,-88.49), material_s1));
    world.add(make_shared<triangle>(point3(323.39,0.00,-88.60), point3(323.99,0.00,-139.34), point3(323.39,20.00,-88.60), material_s1));
    world.add(make_shared<triangle>(point3(323.99,0.00,-139.34), point3(308.23,0.00,-139.45), point3(323.99,20.00,-139.34), material_s1));
    world.add(make_shared<triangle>(point3(308.23,0.00,-139.45), point3(308.06,0.00,-127.83), point3(308.23,20.00,-139.45), material_s1));
    world.add(make_shared<triangle>(point3(308.06,0.00,-127.83), point3(294.20,0.00,-127.94), point3(308.06,20.00,-127.83), material_s1));
    world.add(make_shared<triangle>(point3(294.20,0.00,-127.94), point3(294.37,0.00,-139.11), point3(294.20,20.00,-127.94), material_s1));
    world.add(make_shared<triangle>(point3(294.37,0.00,-139.11), point3(279.48,0.00,-139.23), point3(294.37,20.00,-139.11), material_s1));
    world.add(make_shared<triangle>(point3(279.48,0.00,-139.23), point3(278.79,0.00,-88.49), point3(279.48,20.00,-139.23), material_s1));
    world.add(make_shared<triangle>(point3(278.79,0.00,-88.49), point3(266.65,0.00,-88.60), point3(278.79,20.00,-88.49), material_s1));
    world.add(make_shared<triangle>(point3(266.65,0.00,-88.60), point3(266.91,0.00,-107.26), point3(266.65,20.00,-88.60), material_s1));
    world.add(make_shared<triangle>(point3(266.91,0.00,-107.26), point3(263.38,0.00,-107.38), point3(266.91,20.00,-107.26), material_s1));
    world.add(make_shared<triangle>(point3(263.38,0.00,-107.38), point3(263.81,0.00,-143.14), point3(263.38,20.00,-107.38), material_s1));
    world.add(make_shared<triangle>(point3(263.81,0.00,-143.14), point3(238.06,0.00,-143.47), point3(263.81,20.00,-143.14), material_s1));
    world.add(make_shared<triangle>(point3(238.06,0.00,-143.47), point3(237.37,0.00,-87.60), point3(238.06,20.00,-143.47), material_s1));
    world.add(make_shared<triangle>(point3(237.37,0.00,-87.60), point3(222.48,0.00,-87.82), point3(237.37,20.00,-87.60), material_s1));
    world.add(make_shared<triangle>(point3(222.48,0.00,-87.82), point3(223.34,0.00,-158.34), point3(222.48,20.00,-87.82), material_s1));
    world.add(make_shared<triangle>(point3(223.34,0.00,-158.34), point3(339.06,0.00,-156.88), point3(223.34,20.00,-158.34), material_s1));
    world.add(make_shared<triangle>(point3(339.06,20.00,-156.88), point3(338.11,20.00,-88.49), point3(338.11,0.00,-88.49), material_s1));
    world.add(make_shared<triangle>(point3(338.11,20.00,-88.49), point3(323.39,20.00,-88.60), point3(323.39,0.00,-88.60), material_s1));
    world.add(make_shared<triangle>(point3(323.39,20.00,-88.60), point3(323.99,20.00,-139.34), point3(323.99,0.00,-139.34), material_s1));
    world.add(make_shared<triangle>(point3(323.99,20.00,-139.34), point3(308.23,20.00,-139.45), point3(308.23,0.00,-139.45), material_s1));
    world.add(make_shared<triangle>(point3(308.23,20.00,-139.45), point3(308.06,20.00,-127.83), point3(308.06,0.00,-127.83), material_s1));
    world.add(make_shared<triangle>(point3(308.06,20.00,-127.83), point3(294.20,20.00,-127.94), point3(294.20,0.00,-127.94), material_s1));
    world.add(make_shared<triangle>(point3(294.20,20.00,-127.94), point3(294.37,20.00,-139.11), point3(294.37,0.00,-139.11), material_s1));
    world.add(make_shared<triangle>(point3(294.37,20.00,-139.11), point3(279.48,20.00,-139.23), point3(279.48,0.00,-139.23), material_s1));
    world.add(make_shared<triangle>(point3(279.48,20.00,-139.23), point3(278.79,20.00,-88.49), point3(278.79,0.00,-88.49), material_s1));
    world.add(make_shared<triangle>(point3(278.79,20.00,-88.49), point3(266.65,20.00,-88.60), point3(266.65,0.00,-88.60), material_s1));
    world.add(make_shared<triangle>(point3(266.65,20.00,-88.60), point3(266.91,20.00,-107.26), point3(266.91,0.00,-107.26), material_s1));
    world.add(make_shared<triangle>(point3(266.91,20.00,-107.26), point3(263.38,20.00,-107.38), point3(263.38,0.00,-107.38), material_s1));
    world.add(make_shared<triangle>(point3(263.38,20.00,-107.38), point3(263.81,20.00,-143.14), point3(263.81,0.00,-143.14), material_s1));
    world.add(make_shared<triangle>(point3(263.81,20.00,-143.14), point3(238.06,20.00,-143.47), point3(238.06,0.00,-143.47), material_s1));
    world.add(make_shared<triangle>(point3(238.06,20.00,-143.47), point3(237.37,20.00,-87.60), point3(237.37,0.00,-87.60), material_s1));
    world.add(make_shared<triangle>(point3(237.37,20.00,-87.60), point3(222.48,20.00,-87.82), point3(222.48,0.00,-87.82), material_s1));
    world.add(make_shared<triangle>(point3(222.48,20.00,-87.82), point3(223.34,20.00,-158.34), point3(223.34,0.00,-158.34), material_s1));
    world.add(make_shared<triangle>(point3(223.34,20.00,-158.34), point3(339.06,20.00,-156.88), point3(339.06,0.00,-156.88), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(257.00,0.00,-79.88), point3(257.00,0.00,-65.92), point3(257.00,20.00,-79.88), material_s1));
    world.add(make_shared<triangle>(point3(257.00,0.00,-65.92), point3(237.89,0.00,-65.92), point3(257.00,20.00,-65.92), material_s1));
    world.add(make_shared<triangle>(point3(237.89,0.00,-65.92), point3(237.89,0.00,-79.88), point3(237.89,20.00,-65.92), material_s1));
    world.add(make_shared<triangle>(point3(237.89,0.00,-79.88), point3(257.00,0.00,-79.88), point3(237.89,20.00,-79.88), material_s1));
    world.add(make_shared<triangle>(point3(257.00,20.00,-79.88), point3(257.00,20.00,-65.92), point3(257.00,0.00,-65.92), material_s1));
    world.add(make_shared<triangle>(point3(257.00,20.00,-65.92), point3(237.89,20.00,-65.92), point3(237.89,0.00,-65.92), material_s1));
    world.add(make_shared<triangle>(point3(237.89,20.00,-65.92), point3(237.89,20.00,-79.88), point3(237.89,0.00,-79.88), material_s1));
    world.add(make_shared<triangle>(point3(237.89,20.00,-79.88), point3(257.00,20.00,-79.88), point3(257.00,0.00,-79.88), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(324.68,0.00,-77.54), point3(324.68,0.00,-56.64), point3(324.68,20.00,-77.54), material_s1));
    world.add(make_shared<triangle>(point3(324.68,0.00,-56.64), point3(317.62,0.00,-56.75), point3(324.68,20.00,-56.64), material_s1));
    world.add(make_shared<triangle>(point3(317.62,0.00,-56.75), point3(317.62,0.00,-61.33), point3(317.62,20.00,-56.75), material_s1));
    world.add(make_shared<triangle>(point3(317.62,0.00,-61.33), point3(285.24,0.00,-61.45), point3(317.62,20.00,-61.33), material_s1));
    world.add(make_shared<triangle>(point3(285.24,0.00,-61.45), point3(285.24,0.00,-56.75), point3(285.24,20.00,-61.45), material_s1));
    world.add(make_shared<triangle>(point3(285.24,0.00,-56.75), point3(279.48,0.00,-56.75), point3(285.24,20.00,-56.75), material_s1));
    world.add(make_shared<triangle>(point3(279.48,0.00,-56.75), point3(279.48,0.00,-61.00), point3(279.48,20.00,-56.75), material_s1));
    world.add(make_shared<triangle>(point3(279.48,0.00,-61.00), point3(277.75,0.00,-61.00), point3(279.48,20.00,-61.00), material_s1));
    world.add(make_shared<triangle>(point3(277.75,0.00,-61.00), point3(277.84,0.00,-77.65), point3(277.75,20.00,-61.00), material_s1));
    world.add(make_shared<triangle>(point3(277.84,0.00,-77.65), point3(324.68,0.00,-77.54), point3(277.84,20.00,-77.65), material_s1));
    world.add(make_shared<triangle>(point3(324.68,20.00,-77.54), point3(324.68,20.00,-56.64), point3(324.68,0.00,-56.64), material_s1));
    world.add(make_shared<triangle>(point3(324.68,20.00,-56.64), point3(317.62,20.00,-56.75), point3(317.62,0.00,-56.75), material_s1));
    world.add(make_shared<triangle>(point3(317.62,20.00,-56.75), point3(317.62,20.00,-61.33), point3(317.62,0.00,-61.33), material_s1));
    world.add(make_shared<triangle>(point3(317.62,20.00,-61.33), point3(285.24,20.00,-61.45), point3(285.24,0.00,-61.45), material_s1));
    world.add(make_shared<triangle>(point3(285.24,20.00,-61.45), point3(285.24,20.00,-56.75), point3(285.24,0.00,-56.75), material_s1));
    world.add(make_shared<triangle>(point3(285.24,20.00,-56.75), point3(279.48,20.00,-56.75), point3(279.48,0.00,-56.75), material_s1));
    world.add(make_shared<triangle>(point3(279.48,20.00,-56.75), point3(279.48,20.00,-61.00), point3(279.48,0.00,-61.00), material_s1));
    world.add(make_shared<triangle>(point3(279.48,20.00,-61.00), point3(277.75,20.00,-61.00), point3(277.75,0.00,-61.00), material_s1));
    world.add(make_shared<triangle>(point3(277.75,20.00,-61.00), point3(277.84,20.00,-77.65), point3(277.84,0.00,-77.65), material_s1));
    world.add(make_shared<triangle>(point3(277.84,20.00,-77.65), point3(324.68,20.00,-77.54), point3(324.68,0.00,-77.54), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(542.25,0.00,-189.85), point3(497.91,0.00,-189.85), point3(542.25,20.00,-189.85), material_s1));
    world.add(make_shared<triangle>(point3(497.91,0.00,-189.85), point3(497.91,0.00,-184.15), point3(497.91,20.00,-189.85), material_s1));
    world.add(make_shared<triangle>(point3(497.91,0.00,-184.15), point3(485.43,0.00,-184.15), point3(497.91,20.00,-184.15), material_s1));
    world.add(make_shared<triangle>(point3(485.43,0.00,-184.15), point3(485.43,0.00,-194.43), point3(485.43,20.00,-184.15), material_s1));
    world.add(make_shared<triangle>(point3(485.43,0.00,-194.43), point3(482.41,0.00,-194.43), point3(485.43,20.00,-194.43), material_s1));
    world.add(make_shared<triangle>(point3(482.41,0.00,-194.43), point3(482.41,0.00,-200.69), point3(482.41,20.00,-194.43), material_s1));
    world.add(make_shared<triangle>(point3(482.41,0.00,-200.69), point3(485.86,0.00,-200.69), point3(482.41,20.00,-200.69), material_s1));
    world.add(make_shared<triangle>(point3(485.86,0.00,-200.69), point3(485.86,0.00,-212.87), point3(485.86,20.00,-200.69), material_s1));
    world.add(make_shared<triangle>(point3(485.86,0.00,-212.87), point3(498.17,0.00,-212.87), point3(485.86,20.00,-212.87), material_s1));
    world.add(make_shared<triangle>(point3(498.17,0.00,-212.87), point3(498.17,0.00,-206.61), point3(498.17,20.00,-212.87), material_s1));
    world.add(make_shared<triangle>(point3(498.17,0.00,-206.61), point3(542.51,0.00,-206.61), point3(498.17,20.00,-206.61), material_s1));
    world.add(make_shared<triangle>(point3(542.51,0.00,-206.61), point3(542.51,0.00,-212.87), point3(542.51,20.00,-206.61), material_s1));
    world.add(make_shared<triangle>(point3(542.51,0.00,-212.87), point3(554.74,0.00,-212.87), point3(542.51,20.00,-212.87), material_s1));
    world.add(make_shared<triangle>(point3(554.74,0.00,-212.87), point3(554.74,0.00,-201.14), point3(554.74,20.00,-212.87), material_s1));
    world.add(make_shared<triangle>(point3(554.74,0.00,-201.14), point3(557.23,0.00,-201.14), point3(554.74,20.00,-201.14), material_s1));
    world.add(make_shared<triangle>(point3(557.23,0.00,-201.14), point3(557.23,0.00,-195.88), point3(557.23,20.00,-201.14), material_s1));
    world.add(make_shared<triangle>(point3(557.23,0.00,-195.88), point3(554.74,0.00,-195.88), point3(557.23,20.00,-195.88), material_s1));
    world.add(make_shared<triangle>(point3(554.74,0.00,-195.88), point3(554.74,0.00,-183.93), point3(554.74,20.00,-195.88), material_s1));
    world.add(make_shared<triangle>(point3(554.74,0.00,-183.93), point3(542.25,0.00,-183.93), point3(554.74,20.00,-183.93), material_s1));
    world.add(make_shared<triangle>(point3(542.25,0.00,-183.93), point3(542.25,0.00,-189.85), point3(542.25,20.00,-183.93), material_s1));
    world.add(make_shared<triangle>(point3(542.25,20.00,-189.85), point3(497.91,20.00,-189.85), point3(497.91,0.00,-189.85), material_s1));
    world.add(make_shared<triangle>(point3(497.91,20.00,-189.85), point3(497.91,20.00,-184.15), point3(497.91,0.00,-184.15), material_s1));
    world.add(make_shared<triangle>(point3(497.91,20.00,-184.15), point3(485.43,20.00,-184.15), point3(485.43,0.00,-184.15), material_s1));
    world.add(make_shared<triangle>(point3(485.43,20.00,-184.15), point3(485.43,20.00,-194.43), point3(485.43,0.00,-194.43), material_s1));
    world.add(make_shared<triangle>(point3(485.43,20.00,-194.43), point3(482.41,20.00,-194.43), point3(482.41,0.00,-194.43), material_s1));
    world.add(make_shared<triangle>(point3(482.41,20.00,-194.43), point3(482.41,20.00,-200.69), point3(482.41,0.00,-200.69), material_s1));
    world.add(make_shared<triangle>(point3(482.41,20.00,-200.69), point3(485.86,20.00,-200.69), point3(485.86,0.00,-200.69), material_s1));
    world.add(make_shared<triangle>(point3(485.86,20.00,-200.69), point3(485.86,20.00,-212.87), point3(485.86,0.00,-212.87), material_s1));
    world.add(make_shared<triangle>(point3(485.86,20.00,-212.87), point3(498.17,20.00,-212.87), point3(498.17,0.00,-212.87), material_s1));
    world.add(make_shared<triangle>(point3(498.17,20.00,-212.87), point3(498.17,20.00,-206.61), point3(498.17,0.00,-206.61), material_s1));
    world.add(make_shared<triangle>(point3(498.17,20.00,-206.61), point3(542.51,20.00,-206.61), point3(542.51,0.00,-206.61), material_s1));
    world.add(make_shared<triangle>(point3(542.51,20.00,-206.61), point3(542.51,20.00,-212.87), point3(542.51,0.00,-212.87), material_s1));
    world.add(make_shared<triangle>(point3(542.51,20.00,-212.87), point3(554.74,20.00,-212.87), point3(554.74,0.00,-212.87), material_s1));
    world.add(make_shared<triangle>(point3(554.74,20.00,-212.87), point3(554.74,20.00,-201.14), point3(554.74,0.00,-201.14), material_s1));
    world.add(make_shared<triangle>(point3(554.74,20.00,-201.14), point3(557.23,20.00,-201.14), point3(557.23,0.00,-201.14), material_s1));
    world.add(make_shared<triangle>(point3(557.23,20.00,-201.14), point3(557.23,20.00,-195.88), point3(557.23,0.00,-195.88), material_s1));
    world.add(make_shared<triangle>(point3(557.23,20.00,-195.88), point3(554.74,20.00,-195.88), point3(554.74,0.00,-195.88), material_s1));
    world.add(make_shared<triangle>(point3(554.74,20.00,-195.88), point3(554.74,20.00,-183.93), point3(554.74,0.00,-183.93), material_s1));
    world.add(make_shared<triangle>(point3(554.74,20.00,-183.93), point3(542.25,20.00,-183.93), point3(542.25,0.00,-183.93), material_s1));
    world.add(make_shared<triangle>(point3(542.25,20.00,-183.93), point3(542.25,20.00,-189.85), point3(542.25,0.00,-189.85), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(567.22,0.00,-81.56), point3(567.22,0.00,-63.57), point3(567.22,20.00,-81.56), material_s1));
    world.add(make_shared<triangle>(point3(567.22,0.00,-63.57), point3(539.93,0.00,-63.57), point3(567.22,20.00,-63.57), material_s1));
    world.add(make_shared<triangle>(point3(539.93,0.00,-63.57), point3(539.93,0.00,-81.56), point3(539.93,20.00,-63.57), material_s1));
    world.add(make_shared<triangle>(point3(539.93,0.00,-81.56), point3(567.22,0.00,-81.56), point3(539.93,20.00,-81.56), material_s1));
    world.add(make_shared<triangle>(point3(567.22,20.00,-81.56), point3(567.22,20.00,-63.57), point3(567.22,0.00,-63.57), material_s1));
    world.add(make_shared<triangle>(point3(567.22,20.00,-63.57), point3(539.93,20.00,-63.57), point3(539.93,0.00,-63.57), material_s1));
    world.add(make_shared<triangle>(point3(539.93,20.00,-63.57), point3(539.93,20.00,-81.56), point3(539.93,0.00,-81.56), material_s1));
    world.add(make_shared<triangle>(point3(539.93,20.00,-81.56), point3(567.22,20.00,-81.56), point3(567.22,0.00,-81.56), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(553.62,0.00,9.07), point3(516.94,0.00,8.51), point3(553.62,20.00,9.07), material_s1));
    world.add(make_shared<triangle>(point3(516.94,0.00,8.51), point3(517.20,0.00,-10.37), point3(516.94,20.00,8.51), material_s1));
    world.add(make_shared<triangle>(point3(517.20,0.00,-10.37), point3(492.83,0.00,-10.71), point3(517.20,20.00,-10.37), material_s1));
    world.add(make_shared<triangle>(point3(492.83,0.00,-10.71), point3(492.75,0.00,-2.33), point3(492.83,20.00,-10.71), material_s1));
    world.add(make_shared<triangle>(point3(492.75,0.00,-2.33), point3(498.60,0.00,-2.22), point3(492.75,20.00,-2.33), material_s1));
    world.add(make_shared<triangle>(point3(498.60,0.00,-2.22), point3(498.43,0.00,7.95), point3(498.60,20.00,-2.22), material_s1));
    world.add(make_shared<triangle>(point3(498.43,0.00,7.95), point3(482.50,0.00,7.73), point3(498.43,20.00,7.95), material_s1));
    world.add(make_shared<triangle>(point3(482.50,0.00,7.73), point3(482.93,0.00,-17.97), point3(482.50,20.00,7.73), material_s1));
    world.add(make_shared<triangle>(point3(482.93,0.00,-17.97), point3(479.14,0.00,-18.09), point3(482.93,20.00,-17.97), material_s1));
    world.add(make_shared<triangle>(point3(479.14,0.00,-18.09), point3(479.23,0.00,-26.80), point3(479.14,20.00,-18.09), material_s1));
    world.add(make_shared<triangle>(point3(479.23,0.00,-26.80), point3(566.62,0.00,-25.46), point3(479.23,20.00,-26.80), material_s1));
    world.add(make_shared<triangle>(point3(566.62,0.00,-25.46), point3(566.36,0.00,-10.60), point3(566.62,20.00,-25.46), material_s1));
    world.add(make_shared<triangle>(point3(566.36,0.00,-10.60), point3(559.47,0.00,-10.71), point3(566.36,20.00,-10.60), material_s1));
    world.add(make_shared<triangle>(point3(559.47,0.00,-10.71), point3(559.56,0.00,-15.96), point3(559.47,20.00,-10.71), material_s1));
    world.add(make_shared<triangle>(point3(559.56,0.00,-15.96), point3(554.05,0.00,-16.07), point3(559.56,20.00,-15.96), material_s1));
    world.add(make_shared<triangle>(point3(554.05,0.00,-16.07), point3(553.62,0.00,9.07), point3(554.05,20.00,-16.07), material_s1));
    world.add(make_shared<triangle>(point3(553.62,20.00,9.07), point3(516.94,20.00,8.51), point3(516.94,0.00,8.51), material_s1));
    world.add(make_shared<triangle>(point3(516.94,20.00,8.51), point3(517.20,20.00,-10.37), point3(517.20,0.00,-10.37), material_s1));
    world.add(make_shared<triangle>(point3(517.20,20.00,-10.37), point3(492.83,20.00,-10.71), point3(492.83,0.00,-10.71), material_s1));
    world.add(make_shared<triangle>(point3(492.83,20.00,-10.71), point3(492.75,20.00,-2.33), point3(492.75,0.00,-2.33), material_s1));
    world.add(make_shared<triangle>(point3(492.75,20.00,-2.33), point3(498.60,20.00,-2.22), point3(498.60,0.00,-2.22), material_s1));
    world.add(make_shared<triangle>(point3(498.60,20.00,-2.22), point3(498.43,20.00,7.95), point3(498.43,0.00,7.95), material_s1));
    world.add(make_shared<triangle>(point3(498.43,20.00,7.95), point3(482.50,20.00,7.73), point3(482.50,0.00,7.73), material_s1));
    world.add(make_shared<triangle>(point3(482.50,20.00,7.73), point3(482.93,20.00,-17.97), point3(482.93,0.00,-17.97), material_s1));
    world.add(make_shared<triangle>(point3(482.93,20.00,-17.97), point3(479.14,20.00,-18.09), point3(479.14,0.00,-18.09), material_s1));
    world.add(make_shared<triangle>(point3(479.14,20.00,-18.09), point3(479.23,20.00,-26.80), point3(479.23,0.00,-26.80), material_s1));
    world.add(make_shared<triangle>(point3(479.23,20.00,-26.80), point3(566.62,20.00,-25.46), point3(566.62,0.00,-25.46), material_s1));
    world.add(make_shared<triangle>(point3(566.62,20.00,-25.46), point3(566.36,20.00,-10.60), point3(566.36,0.00,-10.60), material_s1));
    world.add(make_shared<triangle>(point3(566.36,20.00,-10.60), point3(559.47,20.00,-10.71), point3(559.47,0.00,-10.71), material_s1));
    world.add(make_shared<triangle>(point3(559.47,20.00,-10.71), point3(559.56,20.00,-15.96), point3(559.56,0.00,-15.96), material_s1));
    world.add(make_shared<triangle>(point3(559.56,20.00,-15.96), point3(554.05,20.00,-16.07), point3(554.05,0.00,-16.07), material_s1));
    world.add(make_shared<triangle>(point3(554.05,20.00,-16.07), point3(553.62,20.00,9.07), point3(553.62,0.00,9.07), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(38.91,0.00,-401.17), point3(16.53,0.00,-400.73), point3(38.91,20.00,-401.17), material_s1));
    world.add(make_shared<triangle>(point3(16.53,0.00,-400.73), point3(16.18,0.00,-418.83), point3(16.53,20.00,-400.73), material_s1));
    world.add(make_shared<triangle>(point3(16.18,0.00,-418.83), point3(38.57,0.00,-419.28), point3(16.18,20.00,-418.83), material_s1));
    world.add(make_shared<triangle>(point3(38.57,0.00,-419.28), point3(38.91,0.00,-401.17), point3(38.57,20.00,-419.28), material_s1));
    world.add(make_shared<triangle>(point3(38.91,20.00,-401.17), point3(16.53,20.00,-400.73), point3(16.53,0.00,-400.73), material_s1));
    world.add(make_shared<triangle>(point3(16.53,20.00,-400.73), point3(16.18,20.00,-418.83), point3(16.18,0.00,-418.83), material_s1));
    world.add(make_shared<triangle>(point3(16.18,20.00,-418.83), point3(38.57,20.00,-419.28), point3(38.57,0.00,-419.28), material_s1));
    world.add(make_shared<triangle>(point3(38.57,20.00,-419.28), point3(38.91,20.00,-401.17), point3(38.91,0.00,-401.17), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(18.51,0.00,-384.75), point3(18.51,0.00,-391.23), point3(18.51,20.00,-384.75), material_s1));
    world.add(make_shared<triangle>(point3(18.51,0.00,-391.23), point3(27.46,0.00,-391.23), point3(18.51,20.00,-391.23), material_s1));
    world.add(make_shared<triangle>(point3(27.46,0.00,-391.23), point3(27.46,0.00,-384.75), point3(27.46,20.00,-391.23), material_s1));
    world.add(make_shared<triangle>(point3(27.46,0.00,-384.75), point3(18.51,0.00,-384.75), point3(27.46,20.00,-384.75), material_s1));
    world.add(make_shared<triangle>(point3(18.51,20.00,-384.75), point3(18.51,20.00,-391.23), point3(18.51,0.00,-391.23), material_s1));
    world.add(make_shared<triangle>(point3(18.51,20.00,-391.23), point3(27.46,20.00,-391.23), point3(27.46,0.00,-391.23), material_s1));
    world.add(make_shared<triangle>(point3(27.46,20.00,-391.23), point3(27.46,20.00,-384.75), point3(27.46,0.00,-384.75), material_s1));
    world.add(make_shared<triangle>(point3(27.46,20.00,-384.75), point3(18.51,20.00,-384.75), point3(18.51,0.00,-384.75), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(33.06,0.00,-390.33), point3(33.06,0.00,-396.93), point3(33.06,20.00,-390.33), material_s1));
    world.add(make_shared<triangle>(point3(33.06,0.00,-396.93), point3(53.38,0.00,-396.93), point3(33.06,20.00,-396.93), material_s1));
    world.add(make_shared<triangle>(point3(53.38,0.00,-396.93), point3(53.38,0.00,-391.45), point3(53.38,20.00,-396.93), material_s1));
    world.add(make_shared<triangle>(point3(53.38,0.00,-391.45), point3(45.97,0.00,-391.45), point3(53.38,20.00,-391.45), material_s1));
    world.add(make_shared<triangle>(point3(45.97,0.00,-391.45), point3(45.97,0.00,-390.33), point3(45.97,20.00,-391.45), material_s1));
    world.add(make_shared<triangle>(point3(45.97,0.00,-390.33), point3(33.06,0.00,-390.33), point3(45.97,20.00,-390.33), material_s1));
    world.add(make_shared<triangle>(point3(33.06,20.00,-390.33), point3(33.06,20.00,-396.93), point3(33.06,0.00,-396.93), material_s1));
    world.add(make_shared<triangle>(point3(33.06,20.00,-396.93), point3(53.38,20.00,-396.93), point3(53.38,0.00,-396.93), material_s1));
    world.add(make_shared<triangle>(point3(53.38,20.00,-396.93), point3(53.38,20.00,-391.45), point3(53.38,0.00,-391.45), material_s1));
    world.add(make_shared<triangle>(point3(53.38,20.00,-391.45), point3(45.97,20.00,-391.45), point3(45.97,0.00,-391.45), material_s1));
    world.add(make_shared<triangle>(point3(45.97,20.00,-391.45), point3(45.97,20.00,-390.33), point3(45.97,0.00,-390.33), material_s1));
    world.add(make_shared<triangle>(point3(45.97,20.00,-390.33), point3(33.06,20.00,-390.33), point3(33.06,0.00,-390.33), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(245.98,0.00,-364.63), point3(206.46,0.00,-364.63), point3(245.98,20.00,-364.63), material_s1));
    world.add(make_shared<triangle>(point3(206.46,0.00,-364.63), point3(206.46,0.00,-375.14), point3(206.46,20.00,-364.63), material_s1));
    world.add(make_shared<triangle>(point3(206.46,0.00,-375.14), point3(221.70,0.00,-375.14), point3(206.46,20.00,-375.14), material_s1));
    world.add(make_shared<triangle>(point3(221.70,0.00,-375.14), point3(221.70,0.00,-404.75), point3(221.70,20.00,-375.14), material_s1));
    world.add(make_shared<triangle>(point3(221.70,0.00,-404.75), point3(234.19,0.00,-404.75), point3(221.70,20.00,-404.75), material_s1));
    world.add(make_shared<triangle>(point3(234.19,0.00,-404.75), point3(234.19,0.00,-379.05), point3(234.19,20.00,-404.75), material_s1));
    world.add(make_shared<triangle>(point3(234.19,0.00,-379.05), point3(230.92,0.00,-379.05), point3(234.19,20.00,-379.05), material_s1));
    world.add(make_shared<triangle>(point3(230.92,0.00,-379.05), point3(230.92,0.00,-375.14), point3(230.92,20.00,-379.05), material_s1));
    world.add(make_shared<triangle>(point3(230.92,0.00,-375.14), point3(245.98,0.00,-375.14), point3(230.92,20.00,-375.14), material_s1));
    world.add(make_shared<triangle>(point3(245.98,0.00,-375.14), point3(245.98,0.00,-364.63), point3(245.98,20.00,-375.14), material_s1));
    world.add(make_shared<triangle>(point3(245.98,20.00,-364.63), point3(206.46,20.00,-364.63), point3(206.46,0.00,-364.63), material_s1));
    world.add(make_shared<triangle>(point3(206.46,20.00,-364.63), point3(206.46,20.00,-375.14), point3(206.46,0.00,-375.14), material_s1));
    world.add(make_shared<triangle>(point3(206.46,20.00,-375.14), point3(221.70,20.00,-375.14), point3(221.70,0.00,-375.14), material_s1));
    world.add(make_shared<triangle>(point3(221.70,20.00,-375.14), point3(221.70,20.00,-404.75), point3(221.70,0.00,-404.75), material_s1));
    world.add(make_shared<triangle>(point3(221.70,20.00,-404.75), point3(234.19,20.00,-404.75), point3(234.19,0.00,-404.75), material_s1));
    world.add(make_shared<triangle>(point3(234.19,20.00,-404.75), point3(234.19,20.00,-379.05), point3(234.19,0.00,-379.05), material_s1));
    world.add(make_shared<triangle>(point3(234.19,20.00,-379.05), point3(230.92,20.00,-379.05), point3(230.92,0.00,-379.05), material_s1));
    world.add(make_shared<triangle>(point3(230.92,20.00,-379.05), point3(230.92,20.00,-375.14), point3(230.92,0.00,-375.14), material_s1));
    world.add(make_shared<triangle>(point3(230.92,20.00,-375.14), point3(245.98,20.00,-375.14), point3(245.98,0.00,-375.14), material_s1));
    world.add(make_shared<triangle>(point3(245.98,20.00,-375.14), point3(245.98,20.00,-364.63), point3(245.98,0.00,-364.63), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(316.76,0.00,-448.56), point3(316.50,0.00,-410.90), point3(316.76,20.00,-448.56), material_s1));
    world.add(make_shared<triangle>(point3(316.50,0.00,-410.90), point3(327.35,0.00,-410.78), point3(316.50,20.00,-410.90), material_s1));
    world.add(make_shared<triangle>(point3(327.35,0.00,-410.78), point3(327.35,0.00,-406.76), point3(327.35,20.00,-410.78), material_s1));
    world.add(make_shared<triangle>(point3(327.35,0.00,-406.76), point3(321.15,0.00,-406.76), point3(327.35,20.00,-406.76), material_s1));
    world.add(make_shared<triangle>(point3(321.15,0.00,-406.76), point3(321.06,0.00,-402.85), point3(321.15,20.00,-406.76), material_s1));
    world.add(make_shared<triangle>(point3(321.06,0.00,-402.85), point3(335.61,0.00,-402.74), point3(321.06,20.00,-402.85), material_s1));
    world.add(make_shared<triangle>(point3(335.61,0.00,-402.74), point3(335.53,0.00,-381.17), point3(335.61,20.00,-402.74), material_s1));
    world.add(make_shared<triangle>(point3(335.53,0.00,-381.17), point3(321.67,0.00,-381.28), point3(335.53,20.00,-381.17), material_s1));
    world.add(make_shared<triangle>(point3(321.67,0.00,-381.28), point3(321.67,0.00,-386.98), point3(321.67,20.00,-381.28), material_s1));
    world.add(make_shared<triangle>(point3(321.67,0.00,-386.98), point3(280.85,0.00,-387.20), point3(321.67,20.00,-386.98), material_s1));
    world.add(make_shared<triangle>(point3(280.85,0.00,-387.20), point3(280.77,0.00,-381.06), point3(280.85,20.00,-387.20), material_s1));
    world.add(make_shared<triangle>(point3(280.77,0.00,-381.06), point3(266.91,0.00,-381.17), point3(280.77,20.00,-381.06), material_s1));
    world.add(make_shared<triangle>(point3(266.91,0.00,-381.17), point3(267.08,0.00,-402.74), point3(266.91,20.00,-381.17), material_s1));
    world.add(make_shared<triangle>(point3(267.08,0.00,-402.74), point3(285.76,0.00,-402.63), point3(267.08,20.00,-402.74), material_s1));
    world.add(make_shared<triangle>(point3(285.76,0.00,-402.63), point3(286.11,0.00,-448.78), point3(285.76,20.00,-402.63), material_s1));
    world.add(make_shared<triangle>(point3(286.11,0.00,-448.78), point3(316.76,0.00,-448.56), point3(286.11,20.00,-448.78), material_s1));
    world.add(make_shared<triangle>(point3(316.76,20.00,-448.56), point3(316.50,20.00,-410.90), point3(316.50,0.00,-410.90), material_s1));
    world.add(make_shared<triangle>(point3(316.50,20.00,-410.90), point3(327.35,20.00,-410.78), point3(327.35,0.00,-410.78), material_s1));
    world.add(make_shared<triangle>(point3(327.35,20.00,-410.78), point3(327.35,20.00,-406.76), point3(327.35,0.00,-406.76), material_s1));
    world.add(make_shared<triangle>(point3(327.35,20.00,-406.76), point3(321.15,20.00,-406.76), point3(321.15,0.00,-406.76), material_s1));
    world.add(make_shared<triangle>(point3(321.15,20.00,-406.76), point3(321.06,20.00,-402.85), point3(321.06,0.00,-402.85), material_s1));
    world.add(make_shared<triangle>(point3(321.06,20.00,-402.85), point3(335.61,20.00,-402.74), point3(335.61,0.00,-402.74), material_s1));
    world.add(make_shared<triangle>(point3(335.61,20.00,-402.74), point3(335.53,20.00,-381.17), point3(335.53,0.00,-381.17), material_s1));
    world.add(make_shared<triangle>(point3(335.53,20.00,-381.17), point3(321.67,20.00,-381.28), point3(321.67,0.00,-381.28), material_s1));
    world.add(make_shared<triangle>(point3(321.67,20.00,-381.28), point3(321.67,20.00,-386.98), point3(321.67,0.00,-386.98), material_s1));
    world.add(make_shared<triangle>(point3(321.67,20.00,-386.98), point3(280.85,20.00,-387.20), point3(280.85,0.00,-387.20), material_s1));
    world.add(make_shared<triangle>(point3(280.85,20.00,-387.20), point3(280.77,20.00,-381.06), point3(280.77,0.00,-381.06), material_s1));
    world.add(make_shared<triangle>(point3(280.77,20.00,-381.06), point3(266.91,20.00,-381.17), point3(266.91,0.00,-381.17), material_s1));
    world.add(make_shared<triangle>(point3(266.91,20.00,-381.17), point3(267.08,20.00,-402.74), point3(267.08,0.00,-402.74), material_s1));
    world.add(make_shared<triangle>(point3(267.08,20.00,-402.74), point3(285.76,20.00,-402.63), point3(285.76,0.00,-402.63), material_s1));
    world.add(make_shared<triangle>(point3(285.76,20.00,-402.63), point3(286.11,20.00,-448.78), point3(286.11,0.00,-448.78), material_s1));
    world.add(make_shared<triangle>(point3(286.11,20.00,-448.78), point3(316.76,20.00,-448.56), point3(316.76,0.00,-448.56), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(360.07,0.00,-441.07), point3(360.07,0.00,-419.50), point3(360.07,20.00,-441.07), material_s1));
    world.add(make_shared<triangle>(point3(360.07,0.00,-419.50), point3(347.06,0.00,-419.50), point3(360.07,20.00,-419.50), material_s1));
    world.add(make_shared<triangle>(point3(347.06,0.00,-419.50), point3(347.06,0.00,-441.07), point3(347.06,20.00,-419.50), material_s1));
    world.add(make_shared<triangle>(point3(347.06,0.00,-441.07), point3(360.07,0.00,-441.07), point3(347.06,20.00,-441.07), material_s1));
    world.add(make_shared<triangle>(point3(360.07,20.00,-441.07), point3(360.07,20.00,-419.50), point3(360.07,0.00,-419.50), material_s1));
    world.add(make_shared<triangle>(point3(360.07,20.00,-419.50), point3(347.06,20.00,-419.50), point3(347.06,0.00,-419.50), material_s1));
    world.add(make_shared<triangle>(point3(347.06,20.00,-419.50), point3(347.06,20.00,-441.07), point3(347.06,0.00,-441.07), material_s1));
    world.add(make_shared<triangle>(point3(347.06,20.00,-441.07), point3(360.07,20.00,-441.07), point3(360.07,0.00,-441.07), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(19.63,0.00,-295.68), point3(19.54,0.00,-288.75), point3(19.63,20.00,-295.68), material_s1));
    world.add(make_shared<triangle>(point3(19.54,0.00,-288.75), point3(24.19,0.00,-288.75), point3(19.54,20.00,-288.75), material_s1));
    world.add(make_shared<triangle>(point3(24.19,0.00,-288.75), point3(24.02,0.00,-277.58), point3(24.19,20.00,-288.75), material_s1));
    world.add(make_shared<triangle>(point3(24.02,0.00,-277.58), point3(16.87,0.00,-277.69), point3(24.02,20.00,-277.58), material_s1));
    world.add(make_shared<triangle>(point3(16.87,0.00,-277.69), point3(16.87,0.00,-277.13), point3(16.87,20.00,-277.69), material_s1));
    world.add(make_shared<triangle>(point3(16.87,0.00,-277.13), point3(11.53,0.00,-277.24), point3(16.87,20.00,-277.13), material_s1));
    world.add(make_shared<triangle>(point3(11.53,0.00,-277.24), point3(11.88,0.00,-295.79), point3(11.53,20.00,-277.24), material_s1));
    world.add(make_shared<triangle>(point3(11.88,0.00,-295.79), point3(19.63,0.00,-295.68), point3(11.88,20.00,-295.79), material_s1));
    world.add(make_shared<triangle>(point3(19.63,20.00,-295.68), point3(19.54,20.00,-288.75), point3(19.54,0.00,-288.75), material_s1));
    world.add(make_shared<triangle>(point3(19.54,20.00,-288.75), point3(24.19,20.00,-288.75), point3(24.19,0.00,-288.75), material_s1));
    world.add(make_shared<triangle>(point3(24.19,20.00,-288.75), point3(24.02,20.00,-277.58), point3(24.02,0.00,-277.58), material_s1));
    world.add(make_shared<triangle>(point3(24.02,20.00,-277.58), point3(16.87,20.00,-277.69), point3(16.87,0.00,-277.69), material_s1));
    world.add(make_shared<triangle>(point3(16.87,20.00,-277.69), point3(16.87,20.00,-277.13), point3(16.87,0.00,-277.13), material_s1));
    world.add(make_shared<triangle>(point3(16.87,20.00,-277.13), point3(11.53,20.00,-277.24), point3(11.53,0.00,-277.24), material_s1));
    world.add(make_shared<triangle>(point3(11.53,20.00,-277.24), point3(11.88,20.00,-295.79), point3(11.88,0.00,-295.79), material_s1));
    world.add(make_shared<triangle>(point3(11.88,20.00,-295.79), point3(19.63,20.00,-295.68), point3(19.63,0.00,-295.68), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(15.93,0.00,-202.48), point3(15.93,0.00,-225.95), point3(15.93,20.00,-202.48), material_s1));
    world.add(make_shared<triangle>(point3(15.93,0.00,-225.95), point3(26.34,0.00,-225.95), point3(15.93,20.00,-225.95), material_s1));
    world.add(make_shared<triangle>(point3(26.34,0.00,-225.95), point3(26.34,0.00,-221.14), point3(26.34,20.00,-225.95), material_s1));
    world.add(make_shared<triangle>(point3(26.34,0.00,-221.14), point3(34.61,0.00,-221.14), point3(26.34,20.00,-221.14), material_s1));
    world.add(make_shared<triangle>(point3(34.61,0.00,-221.14), point3(34.61,0.00,-202.48), point3(34.61,20.00,-221.14), material_s1));
    world.add(make_shared<triangle>(point3(34.61,0.00,-202.48), point3(15.93,0.00,-202.48), point3(34.61,20.00,-202.48), material_s1));
    world.add(make_shared<triangle>(point3(15.93,20.00,-202.48), point3(15.93,20.00,-225.95), point3(15.93,0.00,-225.95), material_s1));
    world.add(make_shared<triangle>(point3(15.93,20.00,-225.95), point3(26.34,20.00,-225.95), point3(26.34,0.00,-225.95), material_s1));
    world.add(make_shared<triangle>(point3(26.34,20.00,-225.95), point3(26.34,20.00,-221.14), point3(26.34,0.00,-221.14), material_s1));
    world.add(make_shared<triangle>(point3(26.34,20.00,-221.14), point3(34.61,20.00,-221.14), point3(34.61,0.00,-221.14), material_s1));
    world.add(make_shared<triangle>(point3(34.61,20.00,-221.14), point3(34.61,20.00,-202.48), point3(34.61,0.00,-202.48), material_s1));
    world.add(make_shared<triangle>(point3(34.61,20.00,-202.48), point3(15.93,20.00,-202.48), point3(15.93,0.00,-202.48), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(68.79,0.00,-187.50), point3(38.74,0.00,-187.84), point3(68.79,20.00,-187.50), material_s1));
    world.add(make_shared<triangle>(point3(38.74,0.00,-187.84), point3(39.17,0.00,-226.06), point3(38.74,20.00,-187.84), material_s1));
    world.add(make_shared<triangle>(point3(39.17,0.00,-226.06), point3(52.52,0.00,-225.95), point3(39.17,20.00,-226.06), material_s1));
    world.add(make_shared<triangle>(point3(52.52,0.00,-225.95), point3(52.43,0.00,-218.35), point3(52.52,20.00,-225.95), material_s1));
    world.add(make_shared<triangle>(point3(52.43,0.00,-218.35), point3(56.65,0.00,-218.23), point3(52.43,20.00,-218.35), material_s1));
    world.add(make_shared<triangle>(point3(56.65,0.00,-218.23), point3(56.56,0.00,-210.52), point3(56.65,20.00,-218.23), material_s1));
    world.add(make_shared<triangle>(point3(56.56,0.00,-210.52), point3(60.78,0.00,-210.41), point3(56.56,20.00,-210.52), material_s1));
    world.add(make_shared<triangle>(point3(60.78,0.00,-210.41), point3(60.70,0.00,-202.81), point3(60.78,20.00,-210.41), material_s1));
    world.add(make_shared<triangle>(point3(60.70,0.00,-202.81), point3(64.92,0.00,-202.81), point3(60.70,20.00,-202.81), material_s1));
    world.add(make_shared<triangle>(point3(64.92,0.00,-202.81), point3(64.83,0.00,-195.44), point3(64.92,20.00,-202.81), material_s1));
    world.add(make_shared<triangle>(point3(64.83,0.00,-195.44), point3(68.88,0.00,-195.44), point3(64.83,20.00,-195.44), material_s1));
    world.add(make_shared<triangle>(point3(68.88,0.00,-195.44), point3(68.79,0.00,-187.50), point3(68.88,20.00,-195.44), material_s1));
    world.add(make_shared<triangle>(point3(68.79,20.00,-187.50), point3(38.74,20.00,-187.84), point3(38.74,0.00,-187.84), material_s1));
    world.add(make_shared<triangle>(point3(38.74,20.00,-187.84), point3(39.17,20.00,-226.06), point3(39.17,0.00,-226.06), material_s1));
    world.add(make_shared<triangle>(point3(39.17,20.00,-226.06), point3(52.52,20.00,-225.95), point3(52.52,0.00,-225.95), material_s1));
    world.add(make_shared<triangle>(point3(52.52,20.00,-225.95), point3(52.43,20.00,-218.35), point3(52.43,0.00,-218.35), material_s1));
    world.add(make_shared<triangle>(point3(52.43,20.00,-218.35), point3(56.65,20.00,-218.23), point3(56.65,0.00,-218.23), material_s1));
    world.add(make_shared<triangle>(point3(56.65,20.00,-218.23), point3(56.56,20.00,-210.52), point3(56.56,0.00,-210.52), material_s1));
    world.add(make_shared<triangle>(point3(56.56,20.00,-210.52), point3(60.78,20.00,-210.41), point3(60.78,0.00,-210.41), material_s1));
    world.add(make_shared<triangle>(point3(60.78,20.00,-210.41), point3(60.70,20.00,-202.81), point3(60.70,0.00,-202.81), material_s1));
    world.add(make_shared<triangle>(point3(60.70,20.00,-202.81), point3(64.92,20.00,-202.81), point3(64.92,0.00,-202.81), material_s1));
    world.add(make_shared<triangle>(point3(64.92,20.00,-202.81), point3(64.83,20.00,-195.44), point3(64.83,0.00,-195.44), material_s1));
    world.add(make_shared<triangle>(point3(64.83,20.00,-195.44), point3(68.88,20.00,-195.44), point3(68.88,0.00,-195.44), material_s1));
    world.add(make_shared<triangle>(point3(68.88,20.00,-195.44), point3(68.79,20.00,-187.50), point3(68.79,0.00,-187.50), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(16.10,0.00,-125.48), point3(15.75,0.00,-196.67), point3(16.10,20.00,-125.48), material_s1));
    world.add(make_shared<triangle>(point3(15.75,0.00,-196.67), point3(26.95,0.00,-196.78), point3(15.75,20.00,-196.67), material_s1));
    world.add(make_shared<triangle>(point3(26.95,0.00,-196.78), point3(26.95,0.00,-189.63), point3(26.95,20.00,-196.78), material_s1));
    world.add(make_shared<triangle>(point3(26.95,0.00,-189.63), point3(31.60,0.00,-189.63), point3(26.95,20.00,-189.63), material_s1));
    world.add(make_shared<triangle>(point3(31.60,0.00,-189.63), point3(31.68,0.00,-173.31), point3(31.60,20.00,-189.63), material_s1));
    world.add(make_shared<triangle>(point3(31.68,0.00,-173.31), point3(36.07,0.00,-173.42), point3(31.68,20.00,-173.31), material_s1));
    world.add(make_shared<triangle>(point3(36.07,0.00,-173.42), point3(36.07,0.00,-163.48), point3(36.07,20.00,-173.42), material_s1));
    world.add(make_shared<triangle>(point3(36.07,0.00,-163.48), point3(41.15,0.00,-163.48), point3(36.07,20.00,-163.48), material_s1));
    world.add(make_shared<triangle>(point3(41.15,0.00,-163.48), point3(41.24,0.00,-153.08), point3(41.15,20.00,-163.48), material_s1));
    world.add(make_shared<triangle>(point3(41.24,0.00,-153.08), point3(49.59,0.00,-153.08), point3(41.24,20.00,-153.08), material_s1));
    world.add(make_shared<triangle>(point3(49.59,0.00,-153.08), point3(49.59,0.00,-140.34), point3(49.59,20.00,-153.08), material_s1));
    world.add(make_shared<triangle>(point3(49.59,0.00,-140.34), point3(53.98,0.00,-140.34), point3(49.59,20.00,-140.34), material_s1));
    world.add(make_shared<triangle>(point3(53.98,0.00,-140.34), point3(54.07,0.00,-125.70), point3(53.98,20.00,-140.34), material_s1));
    world.add(make_shared<triangle>(point3(54.07,0.00,-125.70), point3(16.10,0.00,-125.48), point3(54.07,20.00,-125.70), material_s1));
    world.add(make_shared<triangle>(point3(16.10,20.00,-125.48), point3(15.75,20.00,-196.67), point3(15.75,0.00,-196.67), material_s1));
    world.add(make_shared<triangle>(point3(15.75,20.00,-196.67), point3(26.95,20.00,-196.78), point3(26.95,0.00,-196.78), material_s1));
    world.add(make_shared<triangle>(point3(26.95,20.00,-196.78), point3(26.95,20.00,-189.63), point3(26.95,0.00,-189.63), material_s1));
    world.add(make_shared<triangle>(point3(26.95,20.00,-189.63), point3(31.60,20.00,-189.63), point3(31.60,0.00,-189.63), material_s1));
    world.add(make_shared<triangle>(point3(31.60,20.00,-189.63), point3(31.68,20.00,-173.31), point3(31.68,0.00,-173.31), material_s1));
    world.add(make_shared<triangle>(point3(31.68,20.00,-173.31), point3(36.07,20.00,-173.42), point3(36.07,0.00,-173.42), material_s1));
    world.add(make_shared<triangle>(point3(36.07,20.00,-173.42), point3(36.07,20.00,-163.48), point3(36.07,0.00,-163.48), material_s1));
    world.add(make_shared<triangle>(point3(36.07,20.00,-163.48), point3(41.15,20.00,-163.48), point3(41.15,0.00,-163.48), material_s1));
    world.add(make_shared<triangle>(point3(41.15,20.00,-163.48), point3(41.24,20.00,-153.08), point3(41.24,0.00,-153.08), material_s1));
    world.add(make_shared<triangle>(point3(41.24,20.00,-153.08), point3(49.59,20.00,-153.08), point3(49.59,0.00,-153.08), material_s1));
    world.add(make_shared<triangle>(point3(49.59,20.00,-153.08), point3(49.59,20.00,-140.34), point3(49.59,0.00,-140.34), material_s1));
    world.add(make_shared<triangle>(point3(49.59,20.00,-140.34), point3(53.98,20.00,-140.34), point3(53.98,0.00,-140.34), material_s1));
    world.add(make_shared<triangle>(point3(53.98,20.00,-140.34), point3(54.07,20.00,-125.70), point3(54.07,0.00,-125.70), material_s1));
    world.add(make_shared<triangle>(point3(54.07,20.00,-125.70), point3(16.10,20.00,-125.48), point3(16.10,0.00,-125.48), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(54.50,0.00,-185.27), point3(68.10,0.00,-185.27), point3(54.50,20.00,-185.27), material_s1));
    world.add(make_shared<triangle>(point3(68.10,0.00,-185.27), point3(68.10,0.00,-173.53), point3(68.10,20.00,-185.27), material_s1));
    world.add(make_shared<triangle>(point3(68.10,0.00,-173.53), point3(54.50,0.00,-173.53), point3(68.10,20.00,-173.53), material_s1));
    world.add(make_shared<triangle>(point3(54.50,0.00,-173.53), point3(54.50,0.00,-185.27), point3(54.50,20.00,-173.53), material_s1));
    world.add(make_shared<triangle>(point3(54.50,20.00,-185.27), point3(68.10,20.00,-185.27), point3(68.10,0.00,-185.27), material_s1));
    world.add(make_shared<triangle>(point3(68.10,20.00,-185.27), point3(68.10,20.00,-173.53), point3(68.10,0.00,-173.53), material_s1));
    world.add(make_shared<triangle>(point3(68.10,20.00,-173.53), point3(54.50,20.00,-173.53), point3(54.50,0.00,-173.53), material_s1));
    world.add(make_shared<triangle>(point3(54.50,20.00,-173.53), point3(54.50,20.00,-185.27), point3(54.50,0.00,-185.27), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(88.33,0.00,-171.75), point3(88.42,0.00,-156.88), point3(88.33,20.00,-171.75), material_s1));
    world.add(make_shared<triangle>(point3(88.42,0.00,-156.88), point3(59.92,0.00,-156.66), point3(88.42,20.00,-156.88), material_s1));
    world.add(make_shared<triangle>(point3(59.92,0.00,-156.66), point3(59.84,0.00,-171.52), point3(59.92,20.00,-156.66), material_s1));
    world.add(make_shared<triangle>(point3(59.84,0.00,-171.52), point3(88.33,0.00,-171.75), point3(59.84,20.00,-171.52), material_s1));
    world.add(make_shared<triangle>(point3(88.33,20.00,-171.75), point3(88.42,20.00,-156.88), point3(88.42,0.00,-156.88), material_s1));
    world.add(make_shared<triangle>(point3(88.42,20.00,-156.88), point3(59.92,20.00,-156.66), point3(59.92,0.00,-156.66), material_s1));
    world.add(make_shared<triangle>(point3(59.92,20.00,-156.66), point3(59.84,20.00,-171.52), point3(59.84,0.00,-171.52), material_s1));
    world.add(make_shared<triangle>(point3(59.84,20.00,-171.52), point3(88.33,20.00,-171.75), point3(88.33,0.00,-171.75), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(62.59,0.00,-145.37), point3(100.13,0.00,-145.60), point3(62.59,20.00,-145.37), material_s1));
    world.add(make_shared<triangle>(point3(100.13,0.00,-145.60), point3(100.22,0.00,-123.47), point3(100.13,20.00,-145.60), material_s1));
    world.add(make_shared<triangle>(point3(100.22,0.00,-123.47), point3(62.68,0.00,-123.36), point3(100.22,20.00,-123.47), material_s1));
    world.add(make_shared<triangle>(point3(62.68,0.00,-123.36), point3(62.59,0.00,-145.37), point3(62.68,20.00,-123.36), material_s1));
    world.add(make_shared<triangle>(point3(62.59,20.00,-145.37), point3(100.13,20.00,-145.60), point3(100.13,0.00,-145.60), material_s1));
    world.add(make_shared<triangle>(point3(100.13,20.00,-145.60), point3(100.22,20.00,-123.47), point3(100.22,0.00,-123.47), material_s1));
    world.add(make_shared<triangle>(point3(100.22,20.00,-123.47), point3(62.68,20.00,-123.36), point3(62.68,0.00,-123.36), material_s1));
    world.add(make_shared<triangle>(point3(62.68,20.00,-123.36), point3(62.59,20.00,-145.37), point3(62.59,0.00,-145.37), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(16.01,0.00,-72.06), point3(16.27,0.00,-101.68), point3(16.01,20.00,-72.06), material_s1));
    world.add(make_shared<triangle>(point3(16.27,0.00,-101.68), point3(54.33,0.00,-101.34), point3(16.27,20.00,-101.68), material_s1));
    world.add(make_shared<triangle>(point3(54.33,0.00,-101.34), point3(54.24,0.00,-87.60), point3(54.33,20.00,-101.34), material_s1));
    world.add(make_shared<triangle>(point3(54.24,0.00,-87.60), point3(48.73,0.00,-87.60), point3(54.24,20.00,-87.60), material_s1));
    world.add(make_shared<triangle>(point3(48.73,0.00,-87.60), point3(48.56,0.00,-71.84), point3(48.73,20.00,-87.60), material_s1));
    world.add(make_shared<triangle>(point3(48.56,0.00,-71.84), point3(16.01,0.00,-72.06), point3(48.56,20.00,-71.84), material_s1));
    world.add(make_shared<triangle>(point3(16.01,20.00,-72.06), point3(16.27,20.00,-101.68), point3(16.27,0.00,-101.68), material_s1));
    world.add(make_shared<triangle>(point3(16.27,20.00,-101.68), point3(54.33,20.00,-101.34), point3(54.33,0.00,-101.34), material_s1));
    world.add(make_shared<triangle>(point3(54.33,20.00,-101.34), point3(54.24,20.00,-87.60), point3(54.24,0.00,-87.60), material_s1));
    world.add(make_shared<triangle>(point3(54.24,20.00,-87.60), point3(48.73,20.00,-87.60), point3(48.73,0.00,-87.60), material_s1));
    world.add(make_shared<triangle>(point3(48.73,20.00,-87.60), point3(48.56,20.00,-71.84), point3(48.56,0.00,-71.84), material_s1));
    world.add(make_shared<triangle>(point3(48.56,20.00,-71.84), point3(16.01,20.00,-72.06), point3(16.01,0.00,-72.06), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(98.49,0.00,-101.79), point3(98.41,0.00,-71.06), point3(98.49,20.00,-101.79), material_s1));
    world.add(make_shared<triangle>(point3(98.41,0.00,-71.06), point3(80.07,0.00,-71.06), point3(98.41,20.00,-71.06), material_s1));
    world.add(make_shared<triangle>(point3(80.07,0.00,-71.06), point3(80.07,0.00,-71.84), point3(80.07,20.00,-71.06), material_s1));
    world.add(make_shared<triangle>(point3(80.07,0.00,-71.84), point3(59.84,0.00,-71.84), point3(80.07,20.00,-71.84), material_s1));
    world.add(make_shared<triangle>(point3(59.84,0.00,-71.84), point3(59.92,0.00,-101.90), point3(59.84,20.00,-71.84), material_s1));
    world.add(make_shared<triangle>(point3(59.92,0.00,-101.90), point3(98.49,0.00,-101.79), point3(59.92,20.00,-101.90), material_s1));
    world.add(make_shared<triangle>(point3(98.49,20.00,-101.79), point3(98.41,20.00,-71.06), point3(98.41,0.00,-71.06), material_s1));
    world.add(make_shared<triangle>(point3(98.41,20.00,-71.06), point3(80.07,20.00,-71.06), point3(80.07,0.00,-71.06), material_s1));
    world.add(make_shared<triangle>(point3(80.07,20.00,-71.06), point3(80.07,20.00,-71.84), point3(80.07,0.00,-71.84), material_s1));
    world.add(make_shared<triangle>(point3(80.07,20.00,-71.84), point3(59.84,20.00,-71.84), point3(59.84,0.00,-71.84), material_s1));
    world.add(make_shared<triangle>(point3(59.84,20.00,-71.84), point3(59.92,20.00,-101.90), point3(59.92,0.00,-101.90), material_s1));
    world.add(make_shared<triangle>(point3(59.92,20.00,-101.90), point3(98.49,20.00,-101.79), point3(98.49,0.00,-101.79), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(37.45,0.00,-69.49), point3(37.45,0.00,-55.75), point3(37.45,20.00,-69.49), material_s1));
    world.add(make_shared<triangle>(point3(37.45,0.00,-55.75), point3(23.16,0.00,-55.75), point3(37.45,20.00,-55.75), material_s1));
    world.add(make_shared<triangle>(point3(23.16,0.00,-55.75), point3(23.16,0.00,-69.49), point3(23.16,20.00,-55.75), material_s1));
    world.add(make_shared<triangle>(point3(23.16,0.00,-69.49), point3(37.45,0.00,-69.49), point3(23.16,20.00,-69.49), material_s1));
    world.add(make_shared<triangle>(point3(37.45,20.00,-69.49), point3(37.45,20.00,-55.75), point3(37.45,0.00,-55.75), material_s1));
    world.add(make_shared<triangle>(point3(37.45,20.00,-55.75), point3(23.16,20.00,-55.75), point3(23.16,0.00,-55.75), material_s1));
    world.add(make_shared<triangle>(point3(23.16,20.00,-55.75), point3(23.16,20.00,-69.49), point3(23.16,0.00,-69.49), material_s1));
    world.add(make_shared<triangle>(point3(23.16,20.00,-69.49), point3(37.45,20.00,-69.49), point3(37.45,0.00,-69.49), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(51.74,0.00,-68.37), point3(51.74,0.00,-56.53), point3(51.74,20.00,-68.37), material_s1));
    world.add(make_shared<triangle>(point3(51.74,0.00,-56.53), point3(45.29,0.00,-56.53), point3(51.74,20.00,-56.53), material_s1));
    world.add(make_shared<triangle>(point3(45.29,0.00,-56.53), point3(45.29,0.00,-68.37), point3(45.29,20.00,-56.53), material_s1));
    world.add(make_shared<triangle>(point3(45.29,0.00,-68.37), point3(51.74,0.00,-68.37), point3(45.29,20.00,-68.37), material_s1));
    world.add(make_shared<triangle>(point3(51.74,20.00,-68.37), point3(51.74,20.00,-56.53), point3(51.74,0.00,-56.53), material_s1));
    world.add(make_shared<triangle>(point3(51.74,20.00,-56.53), point3(45.29,20.00,-56.53), point3(45.29,0.00,-56.53), material_s1));
    world.add(make_shared<triangle>(point3(45.29,20.00,-56.53), point3(45.29,20.00,-68.37), point3(45.29,0.00,-68.37), material_s1));
    world.add(make_shared<triangle>(point3(45.29,20.00,-68.37), point3(51.74,20.00,-68.37), point3(51.74,0.00,-68.37), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(44.34,0.00,-41.11), point3(44.34,0.00,-48.04), point3(44.34,20.00,-41.11), material_s1));
    world.add(make_shared<triangle>(point3(44.34,0.00,-48.04), point3(53.81,0.00,-48.04), point3(44.34,20.00,-48.04), material_s1));
    world.add(make_shared<triangle>(point3(53.81,0.00,-48.04), point3(53.81,0.00,-41.11), point3(53.81,20.00,-48.04), material_s1));
    world.add(make_shared<triangle>(point3(53.81,0.00,-41.11), point3(44.34,0.00,-41.11), point3(53.81,20.00,-41.11), material_s1));
    world.add(make_shared<triangle>(point3(44.34,20.00,-41.11), point3(44.34,20.00,-48.04), point3(44.34,0.00,-48.04), material_s1));
    world.add(make_shared<triangle>(point3(44.34,20.00,-48.04), point3(53.81,20.00,-48.04), point3(53.81,0.00,-48.04), material_s1));
    world.add(make_shared<triangle>(point3(53.81,20.00,-48.04), point3(53.81,20.00,-41.11), point3(53.81,0.00,-41.11), material_s1));
    world.add(make_shared<triangle>(point3(53.81,20.00,-41.11), point3(44.34,20.00,-41.11), point3(44.34,0.00,-41.11), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(23.76,0.00,-26.13), point3(23.76,0.00,-39.77), point3(23.76,20.00,-26.13), material_s1));
    world.add(make_shared<triangle>(point3(23.76,0.00,-39.77), point3(47.78,0.00,-39.77), point3(23.76,20.00,-39.77), material_s1));
    world.add(make_shared<triangle>(point3(47.78,0.00,-39.77), point3(47.78,0.00,-26.13), point3(47.78,20.00,-39.77), material_s1));
    world.add(make_shared<triangle>(point3(47.78,0.00,-26.13), point3(23.76,0.00,-26.13), point3(47.78,20.00,-26.13), material_s1));
    world.add(make_shared<triangle>(point3(23.76,20.00,-26.13), point3(23.76,20.00,-39.77), point3(23.76,0.00,-39.77), material_s1));
    world.add(make_shared<triangle>(point3(23.76,20.00,-39.77), point3(47.78,20.00,-39.77), point3(47.78,0.00,-39.77), material_s1));
    world.add(make_shared<triangle>(point3(47.78,20.00,-39.77), point3(47.78,20.00,-26.13), point3(47.78,0.00,-26.13), material_s1));
    world.add(make_shared<triangle>(point3(47.78,20.00,-26.13), point3(23.76,20.00,-26.13), point3(23.76,0.00,-26.13), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(42.70,0.00,-23.00), point3(42.70,0.00,-10.82), point3(42.70,20.00,-23.00), material_s1));
    world.add(make_shared<triangle>(point3(42.70,0.00,-10.82), point3(23.59,0.00,-10.82), point3(42.70,20.00,-10.82), material_s1));
    world.add(make_shared<triangle>(point3(23.59,0.00,-10.82), point3(23.59,0.00,-23.00), point3(23.59,20.00,-10.82), material_s1));
    world.add(make_shared<triangle>(point3(23.59,0.00,-23.00), point3(42.70,0.00,-23.00), point3(23.59,20.00,-23.00), material_s1));
    world.add(make_shared<triangle>(point3(42.70,20.00,-23.00), point3(42.70,20.00,-10.82), point3(42.70,0.00,-10.82), material_s1));
    world.add(make_shared<triangle>(point3(42.70,20.00,-10.82), point3(23.59,20.00,-10.82), point3(23.59,0.00,-10.82), material_s1));
    world.add(make_shared<triangle>(point3(23.59,20.00,-10.82), point3(23.59,20.00,-23.00), point3(23.59,0.00,-23.00), material_s1));
    world.add(make_shared<triangle>(point3(23.59,20.00,-23.00), point3(42.70,20.00,-23.00), point3(42.70,0.00,-23.00), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(23.59,0.00,-8.25), point3(40.38,0.00,-8.25), point3(23.59,20.00,-8.25), material_s1));
    world.add(make_shared<triangle>(point3(40.38,0.00,-8.25), point3(40.38,0.00,2.48), point3(40.38,20.00,-8.25), material_s1));
    world.add(make_shared<triangle>(point3(40.38,0.00,2.48), point3(23.59,0.00,2.48), point3(40.38,20.00,2.48), material_s1));
    world.add(make_shared<triangle>(point3(23.59,0.00,2.48), point3(23.59,0.00,-8.25), point3(23.59,20.00,2.48), material_s1));
    world.add(make_shared<triangle>(point3(23.59,20.00,-8.25), point3(40.38,20.00,-8.25), point3(40.38,0.00,-8.25), material_s1));
    world.add(make_shared<triangle>(point3(40.38,20.00,-8.25), point3(40.38,20.00,2.48), point3(40.38,0.00,2.48), material_s1));
    world.add(make_shared<triangle>(point3(40.38,20.00,2.48), point3(23.59,20.00,2.48), point3(23.59,0.00,2.48), material_s1));
    world.add(make_shared<triangle>(point3(23.59,20.00,2.48), point3(23.59,20.00,-8.25), point3(23.59,0.00,-8.25), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(77.83,0.00,-12.39), point3(77.83,0.00,-23.67), point3(77.83,20.00,-12.39), material_s1));
    world.add(make_shared<triangle>(point3(77.83,0.00,-23.67), point3(92.38,0.00,-23.67), point3(77.83,20.00,-23.67), material_s1));
    world.add(make_shared<triangle>(point3(92.38,0.00,-23.67), point3(92.38,0.00,-12.39), point3(92.38,20.00,-23.67), material_s1));
    world.add(make_shared<triangle>(point3(92.38,0.00,-12.39), point3(77.83,0.00,-12.39), point3(92.38,20.00,-12.39), material_s1));
    world.add(make_shared<triangle>(point3(77.83,20.00,-12.39), point3(77.83,20.00,-23.67), point3(77.83,0.00,-23.67), material_s1));
    world.add(make_shared<triangle>(point3(77.83,20.00,-23.67), point3(92.38,20.00,-23.67), point3(92.38,0.00,-23.67), material_s1));
    world.add(make_shared<triangle>(point3(92.38,20.00,-23.67), point3(92.38,20.00,-12.39), point3(92.38,0.00,-12.39), material_s1));
    world.add(make_shared<triangle>(point3(92.38,20.00,-12.39), point3(77.83,20.00,-12.39), point3(77.83,0.00,-12.39), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(78.95,0.00,-8.25), point3(93.07,0.00,-8.25), point3(78.95,20.00,-8.25), material_s1));
    world.add(make_shared<triangle>(point3(93.07,0.00,-8.25), point3(93.07,0.00,1.81), point3(93.07,20.00,-8.25), material_s1));
    world.add(make_shared<triangle>(point3(93.07,0.00,1.81), point3(78.95,0.00,1.81), point3(93.07,20.00,1.81), material_s1));
    world.add(make_shared<triangle>(point3(78.95,0.00,1.81), point3(78.95,0.00,-8.25), point3(78.95,20.00,1.81), material_s1));
    world.add(make_shared<triangle>(point3(78.95,20.00,-8.25), point3(93.07,20.00,-8.25), point3(93.07,0.00,-8.25), material_s1));
    world.add(make_shared<triangle>(point3(93.07,20.00,-8.25), point3(93.07,20.00,1.81), point3(93.07,0.00,1.81), material_s1));
    world.add(make_shared<triangle>(point3(93.07,20.00,1.81), point3(78.95,20.00,1.81), point3(78.95,0.00,1.81), material_s1));
    world.add(make_shared<triangle>(point3(78.95,20.00,1.81), point3(78.95,20.00,-8.25), point3(78.95,0.00,-8.25), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(148.95,0.00,-76.31), point3(148.78,0.00,-62.56), point3(148.95,20.00,-76.31), material_s1));
    world.add(make_shared<triangle>(point3(148.78,0.00,-62.56), point3(153.00,0.00,-62.56), point3(148.78,20.00,-62.56), material_s1));
    world.add(make_shared<triangle>(point3(153.00,0.00,-62.56), point3(152.91,0.00,-53.85), point3(153.00,20.00,-62.56), material_s1));
    world.add(make_shared<triangle>(point3(152.91,0.00,-53.85), point3(147.31,0.00,-53.85), point3(152.91,20.00,-53.85), material_s1));
    world.add(make_shared<triangle>(point3(147.31,0.00,-53.85), point3(147.23,0.00,-46.81), point3(147.31,20.00,-53.85), material_s1));
    world.add(make_shared<triangle>(point3(147.23,0.00,-46.81), point3(139.39,0.00,-46.81), point3(147.23,20.00,-46.81), material_s1));
    world.add(make_shared<triangle>(point3(139.39,0.00,-46.81), point3(139.48,0.00,-50.61), point3(139.39,20.00,-46.81), material_s1));
    world.add(make_shared<triangle>(point3(139.48,0.00,-50.61), point3(135.52,0.00,-50.72), point3(139.48,20.00,-50.61), material_s1));
    world.add(make_shared<triangle>(point3(135.52,0.00,-50.72), point3(135.60,0.00,-57.20), point3(135.52,20.00,-50.72), material_s1));
    world.add(make_shared<triangle>(point3(135.60,0.00,-57.20), point3(133.02,0.00,-57.20), point3(135.60,20.00,-57.20), material_s1));
    world.add(make_shared<triangle>(point3(133.02,0.00,-57.20), point3(133.19,0.00,-69.38), point3(133.02,20.00,-57.20), material_s1));
    world.add(make_shared<triangle>(point3(133.19,0.00,-69.38), point3(135.69,0.00,-69.38), point3(133.19,20.00,-69.38), material_s1));
    world.add(make_shared<triangle>(point3(135.69,0.00,-69.38), point3(135.78,0.00,-76.53), point3(135.69,20.00,-69.38), material_s1));
    world.add(make_shared<triangle>(point3(135.78,0.00,-76.53), point3(148.95,0.00,-76.31), point3(135.78,20.00,-76.53), material_s1));
    world.add(make_shared<triangle>(point3(148.95,20.00,-76.31), point3(148.78,20.00,-62.56), point3(148.78,0.00,-62.56), material_s1));
    world.add(make_shared<triangle>(point3(148.78,20.00,-62.56), point3(153.00,20.00,-62.56), point3(153.00,0.00,-62.56), material_s1));
    world.add(make_shared<triangle>(point3(153.00,20.00,-62.56), point3(152.91,20.00,-53.85), point3(152.91,0.00,-53.85), material_s1));
    world.add(make_shared<triangle>(point3(152.91,20.00,-53.85), point3(147.31,20.00,-53.85), point3(147.31,0.00,-53.85), material_s1));
    world.add(make_shared<triangle>(point3(147.31,20.00,-53.85), point3(147.23,20.00,-46.81), point3(147.23,0.00,-46.81), material_s1));
    world.add(make_shared<triangle>(point3(147.23,20.00,-46.81), point3(139.39,20.00,-46.81), point3(139.39,0.00,-46.81), material_s1));
    world.add(make_shared<triangle>(point3(139.39,20.00,-46.81), point3(139.48,20.00,-50.61), point3(139.48,0.00,-50.61), material_s1));
    world.add(make_shared<triangle>(point3(139.48,20.00,-50.61), point3(135.52,20.00,-50.72), point3(135.52,0.00,-50.72), material_s1));
    world.add(make_shared<triangle>(point3(135.52,20.00,-50.72), point3(135.60,20.00,-57.20), point3(135.60,0.00,-57.20), material_s1));
    world.add(make_shared<triangle>(point3(135.60,20.00,-57.20), point3(133.02,20.00,-57.20), point3(133.02,0.00,-57.20), material_s1));
    world.add(make_shared<triangle>(point3(133.02,20.00,-57.20), point3(133.19,20.00,-69.38), point3(133.19,0.00,-69.38), material_s1));
    world.add(make_shared<triangle>(point3(133.19,20.00,-69.38), point3(135.69,20.00,-69.38), point3(135.69,0.00,-69.38), material_s1));
    world.add(make_shared<triangle>(point3(135.69,20.00,-69.38), point3(135.78,20.00,-76.53), point3(135.78,0.00,-76.53), material_s1));
    world.add(make_shared<triangle>(point3(135.78,20.00,-76.53), point3(148.95,20.00,-76.31), point3(148.95,0.00,-76.31), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(126.13,0.00,-28.93), point3(126.13,0.00,-39.77), point3(126.13,20.00,-28.93), material_s1));
    world.add(make_shared<triangle>(point3(126.13,0.00,-39.77), point3(141.54,0.00,-39.77), point3(126.13,20.00,-39.77), material_s1));
    world.add(make_shared<triangle>(point3(141.54,0.00,-39.77), point3(141.54,0.00,-28.93), point3(141.54,20.00,-39.77), material_s1));
    world.add(make_shared<triangle>(point3(141.54,0.00,-28.93), point3(126.13,0.00,-28.93), point3(141.54,20.00,-28.93), material_s1));
    world.add(make_shared<triangle>(point3(126.13,20.00,-28.93), point3(126.13,20.00,-39.77), point3(126.13,0.00,-39.77), material_s1));
    world.add(make_shared<triangle>(point3(126.13,20.00,-39.77), point3(141.54,20.00,-39.77), point3(141.54,0.00,-39.77), material_s1));
    world.add(make_shared<triangle>(point3(141.54,20.00,-39.77), point3(141.54,20.00,-28.93), point3(141.54,0.00,-28.93), material_s1));
    world.add(make_shared<triangle>(point3(141.54,20.00,-28.93), point3(126.13,20.00,-28.93), point3(126.13,0.00,-28.93), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(151.45,0.00,-24.23), point3(151.36,0.00,-14.06), point3(151.45,20.00,-24.23), material_s1));
    world.add(make_shared<triangle>(point3(151.36,0.00,-14.06), point3(128.29,0.00,-14.29), point3(151.36,20.00,-14.06), material_s1));
    world.add(make_shared<triangle>(point3(128.29,0.00,-14.29), point3(128.37,0.00,-24.46), point3(128.29,20.00,-14.29), material_s1));
    world.add(make_shared<triangle>(point3(128.37,0.00,-24.46), point3(151.45,0.00,-24.23), point3(128.37,20.00,-24.46), material_s1));
    world.add(make_shared<triangle>(point3(151.45,20.00,-24.23), point3(151.36,20.00,-14.06), point3(151.36,0.00,-14.06), material_s1));
    world.add(make_shared<triangle>(point3(151.36,20.00,-14.06), point3(128.29,20.00,-14.29), point3(128.29,0.00,-14.29), material_s1));
    world.add(make_shared<triangle>(point3(128.29,20.00,-14.29), point3(128.37,20.00,-24.46), point3(128.37,0.00,-24.46), material_s1));
    world.add(make_shared<triangle>(point3(128.37,20.00,-24.46), point3(151.45,20.00,-24.23), point3(151.45,0.00,-24.23), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(130.52,0.00,-6.35), point3(145.51,0.00,-6.46), point3(130.52,20.00,-6.35), material_s1));
    world.add(make_shared<triangle>(point3(145.51,0.00,-6.46), point3(145.51,0.00,2.70), point3(145.51,20.00,-6.46), material_s1));
    world.add(make_shared<triangle>(point3(145.51,0.00,2.70), point3(130.52,0.00,2.81), point3(145.51,20.00,2.70), material_s1));
    world.add(make_shared<triangle>(point3(130.52,0.00,2.81), point3(130.52,0.00,-6.35), point3(130.52,20.00,2.81), material_s1));
    world.add(make_shared<triangle>(point3(130.52,20.00,-6.35), point3(145.51,20.00,-6.46), point3(145.51,0.00,-6.46), material_s1));
    world.add(make_shared<triangle>(point3(145.51,20.00,-6.46), point3(145.51,20.00,2.70), point3(145.51,0.00,2.70), material_s1));
    world.add(make_shared<triangle>(point3(145.51,20.00,2.70), point3(130.52,20.00,2.81), point3(130.52,0.00,2.81), material_s1));
    world.add(make_shared<triangle>(point3(130.52,20.00,2.81), point3(130.52,20.00,-6.35), point3(130.52,0.00,-6.35), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(174.95,0.00,-27.03), point3(183.22,0.00,-27.14), point3(174.95,20.00,-27.03), material_s1));
    world.add(make_shared<triangle>(point3(183.22,0.00,-27.14), point3(183.04,0.00,-36.41), point3(183.22,20.00,-27.14), material_s1));
    world.add(make_shared<triangle>(point3(183.04,0.00,-36.41), point3(175.55,0.00,-36.41), point3(183.04,20.00,-36.41), material_s1));
    world.add(make_shared<triangle>(point3(175.55,0.00,-36.41), point3(175.38,0.00,-53.18), point3(175.55,20.00,-36.41), material_s1));
    world.add(make_shared<triangle>(point3(175.38,0.00,-53.18), point3(196.73,0.00,-53.40), point3(175.38,20.00,-53.18), material_s1));
    world.add(make_shared<triangle>(point3(196.73,0.00,-53.40), point3(197.16,0.00,-13.39), point3(196.73,20.00,-53.40), material_s1));
    world.add(make_shared<triangle>(point3(197.16,0.00,-13.39), point3(175.12,0.00,-13.17), point3(197.16,20.00,-13.39), material_s1));
    world.add(make_shared<triangle>(point3(175.12,0.00,-13.17), point3(174.95,0.00,-27.03), point3(175.12,20.00,-13.17), material_s1));
    world.add(make_shared<triangle>(point3(174.95,20.00,-27.03), point3(183.22,20.00,-27.14), point3(183.22,0.00,-27.14), material_s1));
    world.add(make_shared<triangle>(point3(183.22,20.00,-27.14), point3(183.04,20.00,-36.41), point3(183.04,0.00,-36.41), material_s1));
    world.add(make_shared<triangle>(point3(183.04,20.00,-36.41), point3(175.55,20.00,-36.41), point3(175.55,0.00,-36.41), material_s1));
    world.add(make_shared<triangle>(point3(175.55,20.00,-36.41), point3(175.38,20.00,-53.18), point3(175.38,0.00,-53.18), material_s1));
    world.add(make_shared<triangle>(point3(175.38,20.00,-53.18), point3(196.73,20.00,-53.40), point3(196.73,0.00,-53.40), material_s1));
    world.add(make_shared<triangle>(point3(196.73,20.00,-53.40), point3(197.16,20.00,-13.39), point3(197.16,0.00,-13.39), material_s1));
    world.add(make_shared<triangle>(point3(197.16,20.00,-13.39), point3(175.12,20.00,-13.17), point3(175.12,0.00,-13.17), material_s1));
    world.add(make_shared<triangle>(point3(175.12,20.00,-13.17), point3(174.95,20.00,-27.03), point3(174.95,0.00,-27.03), material_s1));

    // b_336137
    world.add(make_shared<triangle>(point3(237.72,0.00,-17.53), point3(268.37,0.00,2.92), point3(237.72,20.00,-17.53), material_s1));
    world.add(make_shared<triangle>(point3(268.37,0.00,2.92), point3(263.81,0.00,9.74), point3(268.37,20.00,2.92), material_s1));
    world.add(make_shared<triangle>(point3(263.81,0.00,9.74), point3(254.94,0.00,3.82), point3(263.81,20.00,9.74), material_s1));
    world.add(make_shared<triangle>(point3(254.94,0.00,3.82), point3(252.35,0.00,7.62), point3(254.94,20.00,3.82), material_s1));
    world.add(make_shared<triangle>(point3(252.35,0.00,7.62), point3(230.57,0.00,-6.80), point3(252.35,20.00,7.62), material_s1));
    world.add(make_shared<triangle>(point3(230.57,0.00,-6.80), point3(237.72,0.00,-17.53), point3(230.57,20.00,-6.80), material_s1));
    world.add(make_shared<triangle>(point3(237.72,20.00,-17.53), point3(268.37,20.00,2.92), point3(268.37,0.00,2.92), material_s1));
    world.add(make_shared<triangle>(point3(268.37,20.00,2.92), point3(263.81,20.00,9.74), point3(263.81,0.00,9.74), material_s1));
    world.add(make_shared<triangle>(point3(263.81,20.00,9.74), point3(254.94,20.00,3.82), point3(254.94,0.00,3.82), material_s1));
    world.add(make_shared<triangle>(point3(254.94,20.00,3.82), point3(252.35,20.00,7.62), point3(252.35,0.00,7.62), material_s1));
    world.add(make_shared<triangle>(point3(252.35,20.00,7.62), point3(230.57,20.00,-6.80), point3(230.57,0.00,-6.80), material_s1));
    world.add(make_shared<triangle>(point3(230.57,20.00,-6.80), point3(237.72,20.00,-17.53), point3(237.72,0.00,-17.53), material_s1));




    world.add(make_shared<xz_rect>(0, 580, -460, 10, 0, white));

    world.add(make_shared<sphere>(point3( 400, 10, -270), 3, tx_tower));

    return world;
}