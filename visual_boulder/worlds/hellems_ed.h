#include "../headers/rtweekend.h"
#include "../headers/color.h"
#include "../headers/hittable_list.h"
#include "../headers/sphere.h"
#include "../headers/camera.h"
#include "../headers/material.h"
#include "../headers/bounce_hist.h"
#include "../headers/triangle.h"

hittable_list hellems_ed()
{
    hittable_list world;
    

    // auto material_ground = make_shared<lambertian>(color(0.37, 0.37, 0.37));
    // world.add(make_shared<sphere>(point3(35, -1000, 40), 1000, material_ground));

    auto material_ground = make_shared<lambertian>(color(0.37, 0.37, 0.37));
    world.add(make_shared<sphere>(point3(100, -1000, 100), 2653, material_ground));


    
    // buildings
    auto material_s1 = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    

    
    // building0000
    world.add(make_shared<triangle>(point3(108.569,1652.930,110.203), point3(106.143,1652.930,112.935), point3(106.143,1664.818,112.94), material_s1));
    world.add(make_shared<triangle>(point3(108.569,1652.930,110.203), point3(106.143,1664.818,112.935), point3(108.569,1664.818,110.20), material_s1));
    world.add(make_shared<triangle>(point3(106.143,1652.930,112.935), point3(104.786,1652.930,112.932), point3(104.786,1664.818,112.93), material_s1));
    world.add(make_shared<triangle>(point3(106.143,1652.930,112.935), point3(104.786,1664.818,112.932), point3(106.143,1664.818,112.94), material_s1));
    world.add(make_shared<triangle>(point3(104.786,1652.930,112.932), point3(98.673,1652.930,112.918), point3(98.673,1664.818,112.92), material_s1));
    world.add(make_shared<triangle>(point3(104.786,1652.930,112.932), point3(98.673,1664.818,112.918), point3(104.786,1664.818,112.93), material_s1));
    world.add(make_shared<triangle>(point3(98.673,1652.930,112.918), point3(97.870,1652.930,112.916), point3(97.870,1664.818,112.92), material_s1));
    world.add(make_shared<triangle>(point3(98.673,1652.930,112.918), point3(97.870,1664.818,112.916), point3(98.673,1664.818,112.92), material_s1));
    world.add(make_shared<triangle>(point3(97.870,1652.930,112.916), point3(73.043,1652.930,112.858), point3(73.043,1664.818,112.86), material_s1));
    world.add(make_shared<triangle>(point3(97.870,1652.930,112.916), point3(73.043,1664.818,112.858), point3(97.870,1664.818,112.92), material_s1));
    world.add(make_shared<triangle>(point3(73.043,1652.930,112.858), point3(73.041,1652.930,113.605), point3(73.041,1664.818,113.60), material_s1));
    world.add(make_shared<triangle>(point3(73.043,1652.930,112.858), point3(73.041,1664.818,113.605), point3(73.043,1664.818,112.86), material_s1));
    world.add(make_shared<triangle>(point3(73.041,1652.930,113.605), point3(68.219,1652.930,113.594), point3(68.219,1664.818,113.59), material_s1));
    world.add(make_shared<triangle>(point3(73.041,1652.930,113.605), point3(68.219,1664.818,113.594), point3(73.041,1664.818,113.60), material_s1));
    world.add(make_shared<triangle>(point3(68.219,1652.930,113.594), point3(68.222,1652.930,112.518), point3(68.222,1664.818,112.52), material_s1));
    world.add(make_shared<triangle>(point3(68.219,1652.930,113.594), point3(68.222,1664.818,112.518), point3(68.219,1664.818,113.59), material_s1));
    world.add(make_shared<triangle>(point3(68.222,1652.930,112.518), point3(58.025,1652.930,112.495), point3(58.025,1664.818,112.49), material_s1));
    world.add(make_shared<triangle>(point3(68.222,1652.930,112.518), point3(58.025,1664.818,112.495), point3(68.222,1664.818,112.52), material_s1));
    world.add(make_shared<triangle>(point3(58.025,1652.930,112.495), point3(58.052,1652.930,100.565), point3(58.052,1664.818,100.57), material_s1));
    world.add(make_shared<triangle>(point3(58.025,1652.930,112.495), point3(58.052,1664.818,100.565), point3(58.025,1664.818,112.49), material_s1));
    world.add(make_shared<triangle>(point3(58.052,1652.930,100.565), point3(76.601,1652.930,100.608), point3(76.601,1664.818,100.61), material_s1));
    world.add(make_shared<triangle>(point3(58.052,1652.930,100.565), point3(76.601,1664.818,100.608), point3(58.052,1664.818,100.57), material_s1));
    world.add(make_shared<triangle>(point3(76.601,1652.930,100.608), point3(76.608,1652.930,97.514), point3(76.608,1664.818,97.51), material_s1));
    world.add(make_shared<triangle>(point3(76.601,1652.930,100.608), point3(76.608,1664.818,97.514), point3(76.601,1664.818,100.61), material_s1));
    world.add(make_shared<triangle>(point3(76.608,1652.930,97.514), point3(109.873,1652.930,97.591), point3(109.873,1664.818,97.59), material_s1));
    world.add(make_shared<triangle>(point3(76.608,1652.930,97.514), point3(109.873,1664.818,97.591), point3(76.608,1664.818,97.51), material_s1));
    world.add(make_shared<triangle>(point3(109.873,1652.930,97.591), point3(110.863,1652.930,97.593), point3(110.863,1664.818,97.59), material_s1));
    world.add(make_shared<triangle>(point3(109.873,1652.930,97.591), point3(110.863,1664.818,97.593), point3(109.873,1664.818,97.59), material_s1));
    world.add(make_shared<triangle>(point3(110.863,1652.930,97.593), point3(112.024,1652.930,97.596), point3(112.024,1664.818,97.60), material_s1));
    world.add(make_shared<triangle>(point3(110.863,1652.930,97.593), point3(112.024,1664.818,97.596), point3(110.863,1664.818,97.59), material_s1));
    world.add(make_shared<triangle>(point3(112.024,1652.930,97.596), point3(112.267,1652.930,97.596), point3(112.267,1664.818,97.60), material_s1));
    world.add(make_shared<triangle>(point3(112.024,1652.930,97.596), point3(112.267,1664.818,97.596), point3(112.024,1664.818,97.60), material_s1));
    world.add(make_shared<triangle>(point3(112.267,1652.930,97.596), point3(112.274,1652.930,94.754), point3(112.274,1664.818,94.75), material_s1));
    world.add(make_shared<triangle>(point3(112.267,1652.930,97.596), point3(112.274,1664.818,94.754), point3(112.267,1664.818,97.60), material_s1));
    world.add(make_shared<triangle>(point3(112.274,1652.930,94.754), point3(117.302,1652.930,94.766), point3(117.302,1664.818,94.77), material_s1));
    world.add(make_shared<triangle>(point3(112.274,1652.930,94.754), point3(117.302,1664.818,94.766), point3(112.274,1664.818,94.75), material_s1));
    world.add(make_shared<triangle>(point3(117.302,1652.930,94.766), point3(117.299,1652.930,95.966), point3(117.299,1664.818,95.97), material_s1));
    world.add(make_shared<triangle>(point3(117.302,1652.930,94.766), point3(117.299,1664.818,95.966), point3(117.302,1664.818,94.77), material_s1));
    world.add(make_shared<triangle>(point3(117.299,1652.930,95.966), point3(121.582,1652.930,95.976), point3(121.582,1664.818,95.98), material_s1));
    world.add(make_shared<triangle>(point3(117.299,1652.930,95.966), point3(121.582,1664.818,95.976), point3(117.299,1664.818,95.97), material_s1));
    world.add(make_shared<triangle>(point3(121.582,1652.930,95.976), point3(121.584,1652.930,95.047), point3(121.584,1664.818,95.05), material_s1));
    world.add(make_shared<triangle>(point3(121.582,1652.930,95.976), point3(121.584,1664.818,95.047), point3(121.582,1664.818,95.98), material_s1));
    world.add(make_shared<triangle>(point3(121.584,1652.930,95.047), point3(126.321,1652.930,95.058), point3(126.321,1664.818,95.06), material_s1));
    world.add(make_shared<triangle>(point3(121.584,1652.930,95.047), point3(126.321,1664.818,95.058), point3(121.584,1664.818,95.05), material_s1));
    world.add(make_shared<triangle>(point3(126.321,1652.930,95.058), point3(126.303,1652.930,102.962), point3(126.303,1664.818,102.96), material_s1));
    world.add(make_shared<triangle>(point3(126.321,1652.930,95.058), point3(126.303,1664.818,102.962), point3(126.321,1664.818,95.06), material_s1));
    world.add(make_shared<triangle>(point3(126.303,1652.930,102.962), point3(113.060,1652.930,102.840), point3(113.060,1664.818,102.84), material_s1));
    world.add(make_shared<triangle>(point3(126.303,1652.930,102.962), point3(113.060,1664.818,102.840), point3(126.303,1664.818,102.96), material_s1));
    world.add(make_shared<triangle>(point3(113.060,1652.930,102.840), point3(113.080,1652.930,100.669), point3(113.080,1664.818,100.67), material_s1));
    world.add(make_shared<triangle>(point3(113.060,1652.930,102.840), point3(113.080,1664.818,100.669), point3(113.060,1664.818,102.84), material_s1));
    world.add(make_shared<triangle>(point3(113.080,1652.930,100.669), point3(108.658,1652.930,100.628), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(113.080,1652.930,100.669), point3(108.658,1664.818,100.628), point3(113.080,1664.818,100.67), material_s1));
    world.add(make_shared<triangle>(point3(108.658,1652.930,100.628), point3(108.569,1652.930,110.203), point3(108.569,1664.818,110.20), material_s1));
    world.add(make_shared<triangle>(point3(108.658,1652.930,100.628), point3(108.569,1664.818,110.203), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(108.569,1664.818,110.203), point3(106.143,1664.818,112.935), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(106.143,1664.818,112.935), point3(104.786,1664.818,112.932), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(104.786,1664.818,112.932), point3(98.673,1664.818,112.918), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(98.673,1664.818,112.918), point3(97.870,1664.818,112.916), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(97.870,1664.818,112.916), point3(73.043,1664.818,112.858), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(73.041,1664.818,113.605), point3(68.219,1664.818,113.594), point3(73.043,1664.818,112.86), material_s1));
    world.add(make_shared<triangle>(point3(73.043,1664.818,112.858), point3(68.219,1664.818,113.594), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(68.219,1664.818,113.594), point3(68.222,1664.818,112.518), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(68.222,1664.818,112.518), point3(58.025,1664.818,112.495), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(58.052,1664.818,100.565), point3(76.601,1664.818,100.608), point3(58.025,1664.818,112.49), material_s1));
    world.add(make_shared<triangle>(point3(58.025,1664.818,112.495), point3(76.601,1664.818,100.608), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(76.601,1664.818,100.608), point3(76.608,1664.818,97.514), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(76.608,1664.818,97.514), point3(109.873,1664.818,97.591), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(109.873,1664.818,97.591), point3(110.863,1664.818,97.593), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(110.863,1664.818,97.593), point3(112.024,1664.818,97.596), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(112.024,1664.818,97.596), point3(112.267,1664.818,97.596), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(112.274,1664.818,94.754), point3(117.302,1664.818,94.766), point3(112.267,1664.818,97.60), material_s1));
    world.add(make_shared<triangle>(point3(112.267,1664.818,97.596), point3(117.302,1664.818,94.766), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(117.302,1664.818,94.766), point3(117.299,1664.818,95.966), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(117.299,1664.818,95.966), point3(121.582,1664.818,95.976), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(121.584,1664.818,95.047), point3(126.321,1664.818,95.058), point3(121.582,1664.818,95.98), material_s1));
    world.add(make_shared<triangle>(point3(121.582,1664.818,95.976), point3(126.321,1664.818,95.058), point3(108.658,1664.818,100.63), material_s1));
    world.add(make_shared<triangle>(point3(126.303,1664.818,102.962), point3(113.060,1664.818,102.840), point3(126.321,1664.818,95.06), material_s1));
    world.add(make_shared<triangle>(point3(113.060,1664.818,102.840), point3(113.080,1664.818,100.669), point3(126.321,1664.818,95.06), material_s1));
    world.add(make_shared<triangle>(point3(126.321,1664.818,95.058), point3(113.080,1664.818,100.669), point3(108.658,1664.818,100.63), material_s1));

    // building0001
    world.add(make_shared<triangle>(point3(125.189,1652.930,112.441), point3(108.603,1652.930,112.288), point3(108.603,1671.523,112.29), material_s1));
    world.add(make_shared<triangle>(point3(125.189,1652.930,112.441), point3(108.603,1671.523,112.288), point3(125.189,1671.523,112.44), material_s1));
    world.add(make_shared<triangle>(point3(108.603,1652.930,112.288), point3(108.550,1652.930,112.288), point3(108.550,1671.523,112.29), material_s1));
    world.add(make_shared<triangle>(point3(108.603,1652.930,112.288), point3(108.550,1671.523,112.288), point3(108.603,1671.523,112.29), material_s1));
    world.add(make_shared<triangle>(point3(108.550,1652.930,112.288), point3(108.550,1652.930,112.227), point3(108.550,1671.523,112.23), material_s1));
    world.add(make_shared<triangle>(point3(108.550,1652.930,112.288), point3(108.550,1671.523,112.227), point3(108.550,1671.523,112.29), material_s1));
    world.add(make_shared<triangle>(point3(108.550,1652.930,112.227), point3(108.569,1652.930,110.203), point3(108.569,1671.523,110.20), material_s1));
    world.add(make_shared<triangle>(point3(108.550,1652.930,112.227), point3(108.569,1671.523,110.203), point3(108.550,1671.523,112.23), material_s1));
    world.add(make_shared<triangle>(point3(108.569,1652.930,110.203), point3(108.658,1652.930,100.628), point3(108.658,1671.523,100.63), material_s1));
    world.add(make_shared<triangle>(point3(108.569,1652.930,110.203), point3(108.658,1671.523,100.628), point3(108.569,1671.523,110.20), material_s1));
    world.add(make_shared<triangle>(point3(108.658,1652.930,100.628), point3(113.080,1652.930,100.669), point3(113.080,1671.523,100.67), material_s1));
    world.add(make_shared<triangle>(point3(108.658,1652.930,100.628), point3(113.080,1671.523,100.669), point3(108.658,1671.523,100.63), material_s1));
    world.add(make_shared<triangle>(point3(113.080,1652.930,100.669), point3(113.060,1652.930,102.840), point3(113.060,1671.523,102.84), material_s1));
    world.add(make_shared<triangle>(point3(113.080,1652.930,100.669), point3(113.060,1671.523,102.840), point3(113.080,1671.523,100.67), material_s1));
    world.add(make_shared<triangle>(point3(113.060,1652.930,102.840), point3(126.303,1652.930,102.962), point3(126.303,1671.523,102.96), material_s1));
    world.add(make_shared<triangle>(point3(113.060,1652.930,102.840), point3(126.303,1671.523,102.962), point3(113.060,1671.523,102.84), material_s1));
    world.add(make_shared<triangle>(point3(126.303,1652.930,102.962), point3(126.719,1652.930,102.966), point3(126.719,1671.523,102.97), material_s1));
    world.add(make_shared<triangle>(point3(126.303,1652.930,102.962), point3(126.719,1671.523,102.966), point3(126.303,1671.523,102.96), material_s1));
    world.add(make_shared<triangle>(point3(126.719,1652.930,102.966), point3(126.631,1652.930,112.455), point3(126.631,1671.523,112.45), material_s1));
    world.add(make_shared<triangle>(point3(126.719,1652.930,102.966), point3(126.631,1671.523,112.455), point3(126.719,1671.523,102.97), material_s1));
    world.add(make_shared<triangle>(point3(126.631,1652.930,112.455), point3(125.189,1652.930,112.441), point3(125.189,1671.523,112.44), material_s1));
    world.add(make_shared<triangle>(point3(126.631,1652.930,112.455), point3(125.189,1671.523,112.441), point3(126.631,1671.523,112.45), material_s1));
    world.add(make_shared<triangle>(point3(125.189,1671.523,112.441), point3(108.603,1671.523,112.288), point3(126.631,1671.523,112.45), material_s1));
    world.add(make_shared<triangle>(point3(108.550,1671.523,112.288), point3(108.550,1671.523,112.227), point3(108.603,1671.523,112.29), material_s1));
    world.add(make_shared<triangle>(point3(108.603,1671.523,112.288), point3(108.550,1671.523,112.227), point3(126.631,1671.523,112.45), material_s1));
    world.add(make_shared<triangle>(point3(108.550,1671.523,112.227), point3(108.569,1671.523,110.203), point3(126.631,1671.523,112.45), material_s1));
    world.add(make_shared<triangle>(point3(108.569,1671.523,110.203), point3(108.658,1671.523,100.628), point3(126.631,1671.523,112.45), material_s1));
    world.add(make_shared<triangle>(point3(113.080,1671.523,100.669), point3(113.060,1671.523,102.840), point3(108.658,1671.523,100.63), material_s1));
    world.add(make_shared<triangle>(point3(108.658,1671.523,100.628), point3(113.060,1671.523,102.840), point3(126.631,1671.523,112.45), material_s1));
    world.add(make_shared<triangle>(point3(113.060,1671.523,102.840), point3(126.303,1671.523,102.962), point3(126.631,1671.523,112.45), material_s1));
    world.add(make_shared<triangle>(point3(126.303,1671.523,102.962), point3(126.719,1671.523,102.966), point3(126.631,1671.523,112.45), material_s1));

    // building0002
    world.add(make_shared<triangle>(point3(108.775,1652.930,156.841), point3(108.890,1652.930,142.918), point3(108.890,1667.561,142.92), material_s1));
    world.add(make_shared<triangle>(point3(108.775,1652.930,156.841), point3(108.890,1667.561,142.918), point3(108.775,1667.561,156.84), material_s1));
    world.add(make_shared<triangle>(point3(108.890,1652.930,142.918), point3(108.901,1652.930,141.631), point3(108.901,1667.561,141.63), material_s1));
    world.add(make_shared<triangle>(point3(108.890,1652.930,142.918), point3(108.901,1667.561,141.631), point3(108.890,1667.561,142.92), material_s1));
    world.add(make_shared<triangle>(point3(108.901,1652.930,141.631), point3(97.374,1652.930,141.642), point3(97.374,1667.561,141.64), material_s1));
    world.add(make_shared<triangle>(point3(108.901,1652.930,141.631), point3(97.374,1667.561,141.642), point3(108.901,1667.561,141.63), material_s1));
    world.add(make_shared<triangle>(point3(97.374,1652.930,141.642), point3(97.362,1652.930,127.798), point3(97.362,1667.561,127.80), material_s1));
    world.add(make_shared<triangle>(point3(97.374,1652.930,141.642), point3(97.362,1667.561,127.798), point3(97.374,1667.561,141.64), material_s1));
    world.add(make_shared<triangle>(point3(97.362,1652.930,127.798), point3(98.651,1652.930,127.797), point3(98.651,1667.561,127.80), material_s1));
    world.add(make_shared<triangle>(point3(97.362,1652.930,127.798), point3(98.651,1667.561,127.797), point3(97.362,1667.561,127.80), material_s1));
    world.add(make_shared<triangle>(point3(98.651,1652.930,127.797), point3(108.617,1652.930,127.788), point3(108.617,1667.561,127.79), material_s1));
    world.add(make_shared<triangle>(point3(98.651,1652.930,127.797), point3(108.617,1667.561,127.788), point3(98.651,1667.561,127.80), material_s1));
    world.add(make_shared<triangle>(point3(108.617,1652.930,127.788), point3(108.603,1652.930,112.288), point3(108.603,1667.561,112.29), material_s1));
    world.add(make_shared<triangle>(point3(108.617,1652.930,127.788), point3(108.603,1667.561,112.288), point3(108.617,1667.561,127.79), material_s1));
    world.add(make_shared<triangle>(point3(108.603,1652.930,112.288), point3(125.189,1652.930,112.441), point3(125.189,1667.561,112.44), material_s1));
    world.add(make_shared<triangle>(point3(108.603,1652.930,112.288), point3(125.189,1667.561,112.441), point3(108.603,1667.561,112.29), material_s1));
    world.add(make_shared<triangle>(point3(125.189,1652.930,112.441), point3(125.230,1652.930,156.977), point3(125.230,1667.561,156.98), material_s1));
    world.add(make_shared<triangle>(point3(125.189,1652.930,112.441), point3(125.230,1667.561,156.977), point3(125.189,1667.561,112.44), material_s1));
    world.add(make_shared<triangle>(point3(125.230,1652.930,156.977), point3(108.775,1652.930,156.841), point3(108.775,1667.561,156.84), material_s1));
    world.add(make_shared<triangle>(point3(125.230,1652.930,156.977), point3(108.775,1667.561,156.841), point3(125.230,1667.561,156.98), material_s1));
    world.add(make_shared<triangle>(point3(108.775,1667.561,156.841), point3(108.890,1667.561,142.918), point3(125.230,1667.561,156.98), material_s1));
    world.add(make_shared<triangle>(point3(108.890,1667.561,142.918), point3(108.901,1667.561,141.631), point3(125.230,1667.561,156.98), material_s1));
    world.add(make_shared<triangle>(point3(97.374,1667.561,141.642), point3(97.362,1667.561,127.798), point3(108.901,1667.561,141.63), material_s1));
    world.add(make_shared<triangle>(point3(108.901,1667.561,141.631), point3(97.362,1667.561,127.798), point3(125.230,1667.561,156.98), material_s1));
    world.add(make_shared<triangle>(point3(97.362,1667.561,127.798), point3(98.651,1667.561,127.797), point3(125.230,1667.561,156.98), material_s1));
    world.add(make_shared<triangle>(point3(98.651,1667.561,127.797), point3(108.617,1667.561,127.788), point3(125.230,1667.561,156.98), material_s1));
    world.add(make_shared<triangle>(point3(108.617,1667.561,127.788), point3(108.603,1667.561,112.288), point3(125.230,1667.561,156.98), material_s1));
    world.add(make_shared<triangle>(point3(108.603,1667.561,112.288), point3(125.189,1667.561,112.441), point3(125.230,1667.561,156.98), material_s1));

    // building0003
    world.add(make_shared<triangle>(point3(108.775,1652.930,156.841), point3(125.230,1652.930,156.977), point3(125.230,1671.523,156.98), material_s1));
    world.add(make_shared<triangle>(point3(108.775,1652.930,156.841), point3(125.230,1671.523,156.977), point3(108.775,1671.523,156.84), material_s1));
    world.add(make_shared<triangle>(point3(125.230,1652.930,156.977), point3(126.935,1652.930,156.991), point3(126.935,1671.523,156.99), material_s1));
    world.add(make_shared<triangle>(point3(125.230,1652.930,156.977), point3(126.935,1671.523,156.991), point3(125.230,1671.523,156.98), material_s1));
    world.add(make_shared<triangle>(point3(126.935,1652.930,156.991), point3(126.857,1652.930,166.432), point3(126.857,1671.523,166.43), material_s1));
    world.add(make_shared<triangle>(point3(126.935,1652.930,156.991), point3(126.857,1671.523,166.432), point3(126.935,1671.523,156.99), material_s1));
    world.add(make_shared<triangle>(point3(126.857,1652.930,166.432), point3(126.383,1652.930,166.428), point3(126.383,1671.523,166.43), material_s1));
    world.add(make_shared<triangle>(point3(126.857,1652.930,166.432), point3(126.383,1671.523,166.428), point3(126.857,1671.523,166.43), material_s1));
    world.add(make_shared<triangle>(point3(126.383,1652.930,166.428), point3(108.696,1652.930,166.282), point3(108.696,1671.523,166.28), material_s1));
    world.add(make_shared<triangle>(point3(126.383,1652.930,166.428), point3(108.696,1671.523,166.282), point3(126.383,1671.523,166.43), material_s1));
    world.add(make_shared<triangle>(point3(108.696,1652.930,166.282), point3(108.762,1652.930,158.358), point3(108.762,1671.523,158.36), material_s1));
    world.add(make_shared<triangle>(point3(108.696,1652.930,166.282), point3(108.762,1671.523,158.358), point3(108.696,1671.523,166.28), material_s1));
    world.add(make_shared<triangle>(point3(108.762,1652.930,158.358), point3(108.775,1652.930,156.841), point3(108.775,1671.523,156.84), material_s1));
    world.add(make_shared<triangle>(point3(108.762,1652.930,158.358), point3(108.775,1671.523,156.841), point3(108.762,1671.523,158.36), material_s1));
    world.add(make_shared<triangle>(point3(108.775,1671.523,156.841), point3(125.230,1671.523,156.977), point3(108.762,1671.523,158.36), material_s1));
    world.add(make_shared<triangle>(point3(125.230,1671.523,156.977), point3(126.935,1671.523,156.991), point3(108.762,1671.523,158.36), material_s1));
    world.add(make_shared<triangle>(point3(126.935,1671.523,156.991), point3(126.857,1671.523,166.432), point3(108.762,1671.523,158.36), material_s1));
    world.add(make_shared<triangle>(point3(126.857,1671.523,166.432), point3(126.383,1671.523,166.428), point3(108.762,1671.523,158.36), material_s1));
    world.add(make_shared<triangle>(point3(126.383,1671.523,166.428), point3(108.696,1671.523,166.282), point3(108.762,1671.523,158.36), material_s1));

    // building0004
    world.add(make_shared<triangle>(point3(73.013,1652.930,156.521), point3(101.890,1652.930,156.640), point3(101.890,1664.818,156.64), material_s1));
    world.add(make_shared<triangle>(point3(73.013,1652.930,156.521), point3(101.890,1664.818,156.640), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(101.890,1652.930,156.640), point3(106.413,1652.930,156.658), point3(106.413,1664.818,156.66), material_s1));
    world.add(make_shared<triangle>(point3(101.890,1652.930,156.640), point3(106.413,1664.818,156.658), point3(101.890,1664.818,156.64), material_s1));
    world.add(make_shared<triangle>(point3(106.413,1652.930,156.658), point3(106.406,1652.930,158.348), point3(106.406,1664.818,158.35), material_s1));
    world.add(make_shared<triangle>(point3(106.413,1652.930,156.658), point3(106.406,1664.818,158.348), point3(106.413,1664.818,156.66), material_s1));
    world.add(make_shared<triangle>(point3(106.406,1652.930,158.348), point3(107.939,1652.930,158.354), point3(107.939,1664.818,158.35), material_s1));
    world.add(make_shared<triangle>(point3(106.406,1652.930,158.348), point3(107.939,1664.818,158.354), point3(106.406,1664.818,158.35), material_s1));
    world.add(make_shared<triangle>(point3(107.939,1652.930,158.354), point3(108.762,1652.930,158.358), point3(108.762,1664.818,158.36), material_s1));
    world.add(make_shared<triangle>(point3(107.939,1652.930,158.354), point3(108.762,1664.818,158.358), point3(107.939,1664.818,158.35), material_s1));
    world.add(make_shared<triangle>(point3(108.762,1652.930,158.358), point3(108.696,1652.930,166.282), point3(108.696,1664.818,166.28), material_s1));
    world.add(make_shared<triangle>(point3(108.762,1652.930,158.358), point3(108.696,1664.818,166.282), point3(108.762,1664.818,158.36), material_s1));
    world.add(make_shared<triangle>(point3(108.696,1652.930,166.282), point3(126.383,1652.930,166.428), point3(126.383,1664.818,166.43), material_s1));
    world.add(make_shared<triangle>(point3(108.696,1652.930,166.282), point3(126.383,1664.818,166.428), point3(108.696,1664.818,166.28), material_s1));
    world.add(make_shared<triangle>(point3(126.383,1652.930,166.428), point3(126.351,1652.930,174.311), point3(126.351,1664.818,174.31), material_s1));
    world.add(make_shared<triangle>(point3(126.383,1652.930,166.428), point3(126.351,1664.818,174.311), point3(126.383,1664.818,166.43), material_s1));
    world.add(make_shared<triangle>(point3(126.351,1652.930,174.311), point3(121.538,1652.930,174.291), point3(121.538,1664.818,174.29), material_s1));
    world.add(make_shared<triangle>(point3(126.351,1652.930,174.311), point3(121.538,1664.818,174.291), point3(126.351,1664.818,174.31), material_s1));
    world.add(make_shared<triangle>(point3(121.538,1652.930,174.291), point3(121.543,1652.930,173.209), point3(121.543,1664.818,173.21), material_s1));
    world.add(make_shared<triangle>(point3(121.538,1652.930,174.291), point3(121.543,1664.818,173.209), point3(121.538,1664.818,174.29), material_s1));
    world.add(make_shared<triangle>(point3(121.543,1652.930,173.209), point3(117.350,1652.930,173.192), point3(117.350,1664.818,173.19), material_s1));
    world.add(make_shared<triangle>(point3(121.543,1652.930,173.209), point3(117.350,1664.818,173.192), point3(121.543,1664.818,173.21), material_s1));
    world.add(make_shared<triangle>(point3(117.350,1652.930,173.192), point3(117.346,1652.930,174.278), point3(117.346,1664.818,174.28), material_s1));
    world.add(make_shared<triangle>(point3(117.350,1652.930,173.192), point3(117.346,1664.818,174.278), point3(117.350,1664.818,173.19), material_s1));
    world.add(make_shared<triangle>(point3(117.346,1652.930,174.278), point3(112.471,1652.930,174.257), point3(112.471,1664.818,174.26), material_s1));
    world.add(make_shared<triangle>(point3(117.346,1652.930,174.278), point3(112.471,1664.818,174.257), point3(117.346,1664.818,174.28), material_s1));
    world.add(make_shared<triangle>(point3(112.471,1652.930,174.257), point3(112.482,1652.930,171.555), point3(112.482,1664.818,171.55), material_s1));
    world.add(make_shared<triangle>(point3(112.471,1652.930,174.257), point3(112.482,1664.818,171.555), point3(112.471,1664.818,174.26), material_s1));
    world.add(make_shared<triangle>(point3(112.482,1652.930,171.555), point3(76.754,1652.930,171.408), point3(76.754,1664.818,171.41), material_s1));
    world.add(make_shared<triangle>(point3(112.482,1652.930,171.555), point3(76.754,1664.818,171.408), point3(112.482,1664.818,171.55), material_s1));
    world.add(make_shared<triangle>(point3(76.754,1652.930,171.408), point3(76.758,1652.930,170.313), point3(76.758,1664.818,170.31), material_s1));
    world.add(make_shared<triangle>(point3(76.754,1652.930,171.408), point3(76.758,1664.818,170.313), point3(76.754,1664.818,171.41), material_s1));
    world.add(make_shared<triangle>(point3(76.758,1652.930,170.313), point3(73.914,1652.930,170.301), point3(73.914,1664.818,170.30), material_s1));
    world.add(make_shared<triangle>(point3(76.758,1652.930,170.313), point3(73.914,1664.818,170.301), point3(76.758,1664.818,170.31), material_s1));
    world.add(make_shared<triangle>(point3(73.914,1652.930,170.301), point3(73.919,1652.930,169.072), point3(73.919,1664.818,169.07), material_s1));
    world.add(make_shared<triangle>(point3(73.914,1652.930,170.301), point3(73.919,1664.818,169.072), point3(73.914,1664.818,170.30), material_s1));
    world.add(make_shared<triangle>(point3(73.919,1652.930,169.072), point3(58.096,1652.930,169.007), point3(58.096,1664.818,169.01), material_s1));
    world.add(make_shared<triangle>(point3(73.919,1652.930,169.072), point3(58.096,1664.818,169.007), point3(73.919,1664.818,169.07), material_s1));
    world.add(make_shared<triangle>(point3(58.096,1652.930,169.007), point3(58.147,1652.930,156.625), point3(58.147,1664.818,156.62), material_s1));
    world.add(make_shared<triangle>(point3(58.096,1652.930,169.007), point3(58.147,1664.818,156.625), point3(58.096,1664.818,169.01), material_s1));
    world.add(make_shared<triangle>(point3(58.147,1652.930,156.625), point3(68.098,1652.930,156.666), point3(68.098,1664.818,156.67), material_s1));
    world.add(make_shared<triangle>(point3(58.147,1652.930,156.625), point3(68.098,1664.818,156.666), point3(58.147,1664.818,156.62), material_s1));
    world.add(make_shared<triangle>(point3(68.098,1652.930,156.666), point3(68.103,1652.930,155.521), point3(68.103,1664.818,155.52), material_s1));
    world.add(make_shared<triangle>(point3(68.098,1652.930,156.666), point3(68.103,1664.818,155.521), point3(68.098,1664.818,156.67), material_s1));
    world.add(make_shared<triangle>(point3(68.103,1652.930,155.521), point3(73.017,1652.930,155.541), point3(73.017,1664.818,155.54), material_s1));
    world.add(make_shared<triangle>(point3(68.103,1652.930,155.521), point3(73.017,1664.818,155.541), point3(68.103,1664.818,155.52), material_s1));
    world.add(make_shared<triangle>(point3(73.017,1652.930,155.541), point3(73.013,1652.930,156.521), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(73.017,1652.930,155.541), point3(73.013,1664.818,156.521), point3(73.017,1664.818,155.54), material_s1));
    world.add(make_shared<triangle>(point3(101.890,1664.818,156.640), point3(106.413,1664.818,156.658), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(106.413,1664.818,156.658), point3(106.406,1664.818,158.348), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(107.939,1664.818,158.354), point3(108.762,1664.818,158.358), point3(106.406,1664.818,158.35), material_s1));
    world.add(make_shared<triangle>(point3(108.762,1664.818,158.358), point3(108.696,1664.818,166.282), point3(106.406,1664.818,158.35), material_s1));
    world.add(make_shared<triangle>(point3(106.406,1664.818,158.348), point3(108.696,1664.818,166.282), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(126.383,1664.818,166.428), point3(126.351,1664.818,174.311), point3(108.696,1664.818,166.28), material_s1));
    world.add(make_shared<triangle>(point3(108.696,1664.818,166.282), point3(126.351,1664.818,174.311), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(121.538,1664.818,174.291), point3(121.543,1664.818,173.209), point3(126.351,1664.818,174.31), material_s1));
    world.add(make_shared<triangle>(point3(126.351,1664.818,174.311), point3(121.543,1664.818,173.209), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(121.543,1664.818,173.209), point3(117.350,1664.818,173.192), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(117.346,1664.818,174.278), point3(112.471,1664.818,174.257), point3(117.350,1664.818,173.19), material_s1));
    world.add(make_shared<triangle>(point3(112.471,1664.818,174.257), point3(112.482,1664.818,171.555), point3(117.350,1664.818,173.19), material_s1));
    world.add(make_shared<triangle>(point3(117.350,1664.818,173.192), point3(112.482,1664.818,171.555), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(76.754,1664.818,171.408), point3(76.758,1664.818,170.313), point3(112.482,1664.818,171.55), material_s1));
    world.add(make_shared<triangle>(point3(112.482,1664.818,171.555), point3(76.758,1664.818,170.313), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(73.914,1664.818,170.301), point3(73.919,1664.818,169.072), point3(76.758,1664.818,170.31), material_s1));
    world.add(make_shared<triangle>(point3(76.758,1664.818,170.313), point3(73.919,1664.818,169.072), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(73.919,1664.818,169.072), point3(58.096,1664.818,169.007), point3(73.013,1664.818,156.52), material_s1));
    world.add(make_shared<triangle>(point3(73.013,1664.818,156.521), point3(58.096,1664.818,169.007), point3(73.017,1664.818,155.54), material_s1));
    world.add(make_shared<triangle>(point3(58.147,1664.818,156.625), point3(68.098,1664.818,156.666), point3(58.096,1664.818,169.01), material_s1));
    world.add(make_shared<triangle>(point3(58.096,1664.818,169.007), point3(68.098,1664.818,156.666), point3(73.017,1664.818,155.54), material_s1));
    world.add(make_shared<triangle>(point3(68.098,1664.818,156.666), point3(68.103,1664.818,155.521), point3(73.017,1664.818,155.54), material_s1));

    // building0005
    world.add(make_shared<triangle>(point3(71.732,1653.540,71.279), point3(71.212,1653.540,71.279), point3(71.212,1666.342,71.28), material_s1));
    world.add(make_shared<triangle>(point3(71.732,1653.540,71.279), point3(71.212,1666.342,71.279), point3(71.732,1666.342,71.28), material_s1));
    world.add(make_shared<triangle>(point3(71.212,1653.540,71.279), point3(71.216,1653.540,73.919), point3(71.216,1666.342,73.92), material_s1));
    world.add(make_shared<triangle>(point3(71.212,1653.540,71.279), point3(71.216,1666.342,73.919), point3(71.212,1666.342,71.28), material_s1));
    world.add(make_shared<triangle>(point3(71.216,1653.540,73.919), point3(66.795,1653.540,73.927), point3(66.795,1666.342,73.93), material_s1));
    world.add(make_shared<triangle>(point3(71.216,1653.540,73.919), point3(66.795,1666.342,73.927), point3(71.216,1666.342,73.92), material_s1));
    world.add(make_shared<triangle>(point3(66.795,1653.540,73.927), point3(66.793,1653.540,72.913), point3(66.793,1666.342,72.91), material_s1));
    world.add(make_shared<triangle>(point3(66.795,1653.540,73.927), point3(66.793,1666.342,72.913), point3(66.795,1666.342,73.93), material_s1));
    world.add(make_shared<triangle>(point3(66.793,1653.540,72.913), point3(66.793,1653.540,72.626), point3(66.793,1666.342,72.63), material_s1));
    world.add(make_shared<triangle>(point3(66.793,1653.540,72.913), point3(66.793,1666.342,72.626), point3(66.793,1666.342,72.91), material_s1));
    world.add(make_shared<triangle>(point3(66.793,1653.540,72.626), point3(66.576,1653.540,72.626), point3(66.576,1666.342,72.63), material_s1));
    world.add(make_shared<triangle>(point3(66.793,1653.540,72.626), point3(66.576,1666.342,72.626), point3(66.793,1666.342,72.63), material_s1));
    world.add(make_shared<triangle>(point3(66.576,1653.540,72.626), point3(57.603,1653.540,72.641), point3(57.603,1666.342,72.64), material_s1));
    world.add(make_shared<triangle>(point3(66.576,1653.540,72.626), point3(57.603,1666.342,72.641), point3(66.576,1666.342,72.63), material_s1));
    world.add(make_shared<triangle>(point3(57.603,1653.540,72.641), point3(57.598,1653.540,69.830), point3(57.598,1666.342,69.83), material_s1));
    world.add(make_shared<triangle>(point3(57.603,1653.540,72.641), point3(57.598,1666.342,69.830), point3(57.603,1666.342,72.64), material_s1));
    world.add(make_shared<triangle>(point3(57.598,1653.540,69.830), point3(57.052,1653.540,69.831), point3(57.052,1666.342,69.83), material_s1));
    world.add(make_shared<triangle>(point3(57.598,1653.540,69.830), point3(57.052,1666.342,69.831), point3(57.598,1666.342,69.83), material_s1));
    world.add(make_shared<triangle>(point3(57.052,1653.540,69.831), point3(57.033,1653.540,58.919), point3(57.033,1666.342,58.92), material_s1));
    world.add(make_shared<triangle>(point3(57.052,1653.540,69.831), point3(57.033,1666.342,58.919), point3(57.052,1666.342,69.83), material_s1));
    world.add(make_shared<triangle>(point3(57.033,1653.540,58.919), point3(57.751,1653.540,58.918), point3(57.751,1666.342,58.92), material_s1));
    world.add(make_shared<triangle>(point3(57.033,1653.540,58.919), point3(57.751,1666.342,58.918), point3(57.033,1666.342,58.92), material_s1));
    world.add(make_shared<triangle>(point3(57.751,1653.540,58.918), point3(57.747,1653.540,56.625), point3(57.747,1666.342,56.62), material_s1));
    world.add(make_shared<triangle>(point3(57.751,1653.540,58.918), point3(57.747,1666.342,56.625), point3(57.751,1666.342,58.92), material_s1));
    world.add(make_shared<triangle>(point3(57.747,1653.540,56.625), point3(67.768,1653.540,56.608), point3(67.768,1666.342,56.61), material_s1));
    world.add(make_shared<triangle>(point3(57.747,1653.540,56.625), point3(67.768,1666.342,56.608), point3(57.747,1666.342,56.62), material_s1));
    world.add(make_shared<triangle>(point3(67.768,1653.540,56.608), point3(67.769,1653.540,57.181), point3(67.769,1666.342,57.18), material_s1));
    world.add(make_shared<triangle>(point3(67.768,1653.540,56.608), point3(67.769,1666.342,57.181), point3(67.768,1666.342,56.61), material_s1));
    world.add(make_shared<triangle>(point3(67.769,1653.540,57.181), point3(127.770,1653.540,57.077), point3(127.770,1666.342,57.08), material_s1));
    world.add(make_shared<triangle>(point3(67.769,1653.540,57.181), point3(127.770,1666.342,57.077), point3(67.769,1666.342,57.18), material_s1));
    world.add(make_shared<triangle>(point3(127.770,1653.540,57.077), point3(127.789,1653.540,67.759), point3(127.789,1666.342,67.76), material_s1));
    world.add(make_shared<triangle>(point3(127.770,1653.540,57.077), point3(127.789,1666.342,67.759), point3(127.770,1666.342,57.08), material_s1));
    world.add(make_shared<triangle>(point3(127.789,1653.540,67.759), point3(126.421,1653.540,67.761), point3(126.421,1666.342,67.76), material_s1));
    world.add(make_shared<triangle>(point3(127.789,1653.540,67.759), point3(126.421,1666.342,67.761), point3(127.789,1666.342,67.76), material_s1));
    world.add(make_shared<triangle>(point3(126.421,1653.540,67.761), point3(126.456,1653.540,87.941), point3(126.456,1666.342,87.94), material_s1));
    world.add(make_shared<triangle>(point3(126.421,1653.540,67.761), point3(126.456,1666.342,87.941), point3(126.421,1666.342,67.76), material_s1));
    world.add(make_shared<triangle>(point3(126.456,1653.540,87.941), point3(112.365,1653.540,87.965), point3(112.365,1666.342,87.97), material_s1));
    world.add(make_shared<triangle>(point3(126.456,1653.540,87.941), point3(112.365,1666.342,87.965), point3(126.456,1666.342,87.94), material_s1));
    world.add(make_shared<triangle>(point3(112.365,1653.540,87.965), point3(112.336,1653.540,71.209), point3(112.336,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(112.365,1653.540,87.965), point3(112.336,1666.342,71.209), point3(112.365,1666.342,87.97), material_s1));
    world.add(make_shared<triangle>(point3(112.336,1653.540,71.209), point3(109.301,1653.540,71.214), point3(109.301,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(112.336,1653.540,71.209), point3(109.301,1666.342,71.214), point3(112.336,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(109.301,1653.540,71.214), point3(71.732,1653.540,71.279), point3(71.732,1666.342,71.28), material_s1));
    world.add(make_shared<triangle>(point3(109.301,1653.540,71.214), point3(71.732,1666.342,71.279), point3(109.301,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(71.732,1666.342,71.279), point3(71.212,1666.342,71.279), point3(109.301,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(71.216,1666.342,73.919), point3(66.795,1666.342,73.927), point3(71.212,1666.342,71.28), material_s1));
    world.add(make_shared<triangle>(point3(66.795,1666.342,73.927), point3(66.793,1666.342,72.913), point3(71.212,1666.342,71.28), material_s1));
    world.add(make_shared<triangle>(point3(66.793,1666.342,72.913), point3(66.793,1666.342,72.626), point3(71.212,1666.342,71.28), material_s1));
    world.add(make_shared<triangle>(point3(66.793,1666.342,72.626), point3(66.576,1666.342,72.626), point3(71.212,1666.342,71.28), material_s1));
    world.add(make_shared<triangle>(point3(66.576,1666.342,72.626), point3(57.603,1666.342,72.641), point3(71.212,1666.342,71.28), material_s1));
    world.add(make_shared<triangle>(point3(57.603,1666.342,72.641), point3(57.598,1666.342,69.830), point3(71.212,1666.342,71.28), material_s1));
    world.add(make_shared<triangle>(point3(71.212,1666.342,71.279), point3(57.598,1666.342,69.830), point3(109.301,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(57.052,1666.342,69.831), point3(57.033,1666.342,58.919), point3(57.598,1666.342,69.83), material_s1));
    world.add(make_shared<triangle>(point3(57.598,1666.342,69.830), point3(57.033,1666.342,58.919), point3(109.301,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(57.033,1666.342,58.919), point3(57.751,1666.342,58.918), point3(109.301,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(57.751,1666.342,58.918), point3(57.747,1666.342,56.625), point3(109.301,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(67.768,1666.342,56.608), point3(67.769,1666.342,57.181), point3(57.747,1666.342,56.62), material_s1));
    world.add(make_shared<triangle>(point3(57.747,1666.342,56.625), point3(67.769,1666.342,57.181), point3(109.301,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(67.769,1666.342,57.181), point3(127.770,1666.342,57.077), point3(109.301,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(127.789,1666.342,67.759), point3(126.421,1666.342,67.761), point3(127.770,1666.342,57.08), material_s1));
    world.add(make_shared<triangle>(point3(127.770,1666.342,57.077), point3(126.421,1666.342,67.761), point3(109.301,1666.342,71.21), material_s1));
    world.add(make_shared<triangle>(point3(126.456,1666.342,87.941), point3(112.365,1666.342,87.965), point3(126.421,1666.342,67.76), material_s1));
    world.add(make_shared<triangle>(point3(112.365,1666.342,87.965), point3(112.336,1666.342,71.209), point3(126.421,1666.342,67.76), material_s1));
    world.add(make_shared<triangle>(point3(126.421,1666.342,67.761), point3(112.336,1666.342,71.209), point3(109.301,1666.342,71.21), material_s1));




    
    return world;
}