#include "../headers/rtweekend.h"
#include "../headers/color.h"
#include "../headers/hittable_list.h"
#include "../headers/sphere.h"
#include "../headers/camera.h"
#include "../headers/material.h"
#include "../headers/bounce_hist.h"
#include "../headers/triangle.h"

hittable_list hellems()
{
    hittable_list world;
    

    auto material_ground = make_shared<lambertian>(color(0.37, 0.37, 0.37));
    world.add(make_shared<sphere>(point3(-52, -1000, 60), 2653, material_ground));

    // buildings
    auto material_s1 = make_shared<lambertian>(color(0.7, 0.3, 0.3));

    
    // building0000
    world.add(make_shared<triangle>(point3(-54.106,1652.930,59.441), point3(-56.532,1652.930,62.173), point3(-56.532,1664.818,62.17), material_s1));
    world.add(make_shared<triangle>(point3(-54.106,1652.930,59.441), point3(-56.532,1664.818,62.173), point3(-54.106,1664.818,59.44), material_s1));
    world.add(make_shared<triangle>(point3(-56.532,1652.930,62.173), point3(-57.888,1652.930,62.170), point3(-57.888,1664.818,62.17), material_s1));
    world.add(make_shared<triangle>(point3(-56.532,1652.930,62.173), point3(-57.888,1664.818,62.170), point3(-56.532,1664.818,62.17), material_s1));
    world.add(make_shared<triangle>(point3(-57.888,1652.930,62.170), point3(-64.002,1652.930,62.156), point3(-64.002,1664.818,62.16), material_s1));
    world.add(make_shared<triangle>(point3(-57.888,1652.930,62.170), point3(-64.002,1664.818,62.156), point3(-57.888,1664.818,62.17), material_s1));
    world.add(make_shared<triangle>(point3(-64.002,1652.930,62.156), point3(-64.805,1652.930,62.154), point3(-64.805,1664.818,62.15), material_s1));
    world.add(make_shared<triangle>(point3(-64.002,1652.930,62.156), point3(-64.805,1664.818,62.154), point3(-64.002,1664.818,62.16), material_s1));
    world.add(make_shared<triangle>(point3(-64.805,1652.930,62.154), point3(-89.632,1652.930,62.096), point3(-89.632,1664.818,62.10), material_s1));
    world.add(make_shared<triangle>(point3(-64.805,1652.930,62.154), point3(-89.632,1664.818,62.096), point3(-64.805,1664.818,62.15), material_s1));
    world.add(make_shared<triangle>(point3(-89.632,1652.930,62.096), point3(-89.634,1652.930,62.843), point3(-89.634,1664.818,62.84), material_s1));
    world.add(make_shared<triangle>(point3(-89.632,1652.930,62.096), point3(-89.634,1664.818,62.843), point3(-89.632,1664.818,62.10), material_s1));
    world.add(make_shared<triangle>(point3(-89.634,1652.930,62.843), point3(-94.456,1652.930,62.832), point3(-94.456,1664.818,62.83), material_s1));
    world.add(make_shared<triangle>(point3(-89.634,1652.930,62.843), point3(-94.456,1664.818,62.832), point3(-89.634,1664.818,62.84), material_s1));
    world.add(make_shared<triangle>(point3(-94.456,1652.930,62.832), point3(-94.453,1652.930,61.756), point3(-94.453,1664.818,61.76), material_s1));
    world.add(make_shared<triangle>(point3(-94.456,1652.930,62.832), point3(-94.453,1664.818,61.756), point3(-94.456,1664.818,62.83), material_s1));
    world.add(make_shared<triangle>(point3(-94.453,1652.930,61.756), point3(-104.650,1652.930,61.733), point3(-104.650,1664.818,61.73), material_s1));
    world.add(make_shared<triangle>(point3(-94.453,1652.930,61.756), point3(-104.650,1664.818,61.733), point3(-94.453,1664.818,61.76), material_s1));
    world.add(make_shared<triangle>(point3(-104.650,1652.930,61.733), point3(-104.623,1652.930,49.803), point3(-104.623,1664.818,49.80), material_s1));
    world.add(make_shared<triangle>(point3(-104.650,1652.930,61.733), point3(-104.623,1664.818,49.803), point3(-104.650,1664.818,61.73), material_s1));
    world.add(make_shared<triangle>(point3(-104.623,1652.930,49.803), point3(-86.074,1652.930,49.846), point3(-86.074,1664.818,49.85), material_s1));
    world.add(make_shared<triangle>(point3(-104.623,1652.930,49.803), point3(-86.074,1664.818,49.846), point3(-104.623,1664.818,49.80), material_s1));
    world.add(make_shared<triangle>(point3(-86.074,1652.930,49.846), point3(-86.067,1652.930,46.752), point3(-86.067,1664.818,46.75), material_s1));
    world.add(make_shared<triangle>(point3(-86.074,1652.930,49.846), point3(-86.067,1664.818,46.752), point3(-86.074,1664.818,49.85), material_s1));
    world.add(make_shared<triangle>(point3(-86.067,1652.930,46.752), point3(-52.802,1652.930,46.829), point3(-52.802,1664.818,46.83), material_s1));
    world.add(make_shared<triangle>(point3(-86.067,1652.930,46.752), point3(-52.802,1664.818,46.829), point3(-86.067,1664.818,46.75), material_s1));
    world.add(make_shared<triangle>(point3(-52.802,1652.930,46.829), point3(-51.812,1652.930,46.831), point3(-51.812,1664.818,46.83), material_s1));
    world.add(make_shared<triangle>(point3(-52.802,1652.930,46.829), point3(-51.812,1664.818,46.831), point3(-52.802,1664.818,46.83), material_s1));
    world.add(make_shared<triangle>(point3(-51.812,1652.930,46.831), point3(-50.651,1652.930,46.834), point3(-50.651,1664.818,46.83), material_s1));
    world.add(make_shared<triangle>(point3(-51.812,1652.930,46.831), point3(-50.651,1664.818,46.834), point3(-51.812,1664.818,46.83), material_s1));
    world.add(make_shared<triangle>(point3(-50.651,1652.930,46.834), point3(-50.407,1652.930,46.834), point3(-50.407,1664.818,46.83), material_s1));
    world.add(make_shared<triangle>(point3(-50.651,1652.930,46.834), point3(-50.407,1664.818,46.834), point3(-50.651,1664.818,46.83), material_s1));
    world.add(make_shared<triangle>(point3(-50.407,1652.930,46.834), point3(-50.401,1652.930,43.992), point3(-50.401,1664.818,43.99), material_s1));
    world.add(make_shared<triangle>(point3(-50.407,1652.930,46.834), point3(-50.401,1664.818,43.992), point3(-50.407,1664.818,46.83), material_s1));
    world.add(make_shared<triangle>(point3(-50.401,1652.930,43.992), point3(-45.373,1652.930,44.004), point3(-45.373,1664.818,44.00), material_s1));
    world.add(make_shared<triangle>(point3(-50.401,1652.930,43.992), point3(-45.373,1664.818,44.004), point3(-50.401,1664.818,43.99), material_s1));
    world.add(make_shared<triangle>(point3(-45.373,1652.930,44.004), point3(-45.376,1652.930,45.205), point3(-45.376,1664.818,45.20), material_s1));
    world.add(make_shared<triangle>(point3(-45.373,1652.930,44.004), point3(-45.376,1664.818,45.205), point3(-45.373,1664.818,44.00), material_s1));
    world.add(make_shared<triangle>(point3(-45.376,1652.930,45.205), point3(-41.093,1652.930,45.214), point3(-41.093,1664.818,45.21), material_s1));
    world.add(make_shared<triangle>(point3(-45.376,1652.930,45.205), point3(-41.093,1664.818,45.214), point3(-45.376,1664.818,45.20), material_s1));
    world.add(make_shared<triangle>(point3(-41.093,1652.930,45.214), point3(-41.091,1652.930,44.285), point3(-41.091,1664.818,44.28), material_s1));
    world.add(make_shared<triangle>(point3(-41.093,1652.930,45.214), point3(-41.091,1664.818,44.285), point3(-41.093,1664.818,45.21), material_s1));
    world.add(make_shared<triangle>(point3(-41.091,1652.930,44.285), point3(-36.354,1652.930,44.296), point3(-36.354,1664.818,44.30), material_s1));
    world.add(make_shared<triangle>(point3(-41.091,1652.930,44.285), point3(-36.354,1664.818,44.296), point3(-41.091,1664.818,44.28), material_s1));
    world.add(make_shared<triangle>(point3(-36.354,1652.930,44.296), point3(-36.372,1652.930,52.200), point3(-36.372,1664.818,52.20), material_s1));
    world.add(make_shared<triangle>(point3(-36.354,1652.930,44.296), point3(-36.372,1664.818,52.200), point3(-36.354,1664.818,44.30), material_s1));
    world.add(make_shared<triangle>(point3(-36.372,1652.930,52.200), point3(-49.615,1652.930,52.078), point3(-49.615,1664.818,52.08), material_s1));
    world.add(make_shared<triangle>(point3(-36.372,1652.930,52.200), point3(-49.615,1664.818,52.078), point3(-36.372,1664.818,52.20), material_s1));
    world.add(make_shared<triangle>(point3(-49.615,1652.930,52.078), point3(-49.595,1652.930,49.907), point3(-49.595,1664.818,49.91), material_s1));
    world.add(make_shared<triangle>(point3(-49.615,1652.930,52.078), point3(-49.595,1664.818,49.907), point3(-49.615,1664.818,52.08), material_s1));
    world.add(make_shared<triangle>(point3(-49.595,1652.930,49.907), point3(-54.017,1652.930,49.866), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-49.595,1652.930,49.907), point3(-54.017,1664.818,49.866), point3(-49.595,1664.818,49.91), material_s1));
    world.add(make_shared<triangle>(point3(-54.017,1652.930,49.866), point3(-54.106,1652.930,59.441), point3(-54.106,1664.818,59.44), material_s1));
    world.add(make_shared<triangle>(point3(-54.017,1652.930,49.866), point3(-54.106,1664.818,59.441), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-54.106,1664.818,59.441), point3(-56.532,1664.818,62.173), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-56.532,1664.818,62.173), point3(-57.888,1664.818,62.170), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-57.888,1664.818,62.170), point3(-64.002,1664.818,62.156), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-64.002,1664.818,62.156), point3(-64.805,1664.818,62.154), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-64.805,1664.818,62.154), point3(-89.632,1664.818,62.096), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-89.634,1664.818,62.843), point3(-94.456,1664.818,62.832), point3(-89.632,1664.818,62.10), material_s1));
    world.add(make_shared<triangle>(point3(-89.632,1664.818,62.096), point3(-94.456,1664.818,62.832), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-94.456,1664.818,62.832), point3(-94.453,1664.818,61.756), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-94.453,1664.818,61.756), point3(-104.650,1664.818,61.733), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-104.623,1664.818,49.803), point3(-86.074,1664.818,49.846), point3(-104.650,1664.818,61.73), material_s1));
    world.add(make_shared<triangle>(point3(-104.650,1664.818,61.733), point3(-86.074,1664.818,49.846), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-86.074,1664.818,49.846), point3(-86.067,1664.818,46.752), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-86.067,1664.818,46.752), point3(-52.802,1664.818,46.829), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-52.802,1664.818,46.829), point3(-51.812,1664.818,46.831), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-51.812,1664.818,46.831), point3(-50.651,1664.818,46.834), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-50.651,1664.818,46.834), point3(-50.407,1664.818,46.834), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-50.401,1664.818,43.992), point3(-45.373,1664.818,44.004), point3(-50.407,1664.818,46.83), material_s1));
    world.add(make_shared<triangle>(point3(-50.407,1664.818,46.834), point3(-45.373,1664.818,44.004), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-45.373,1664.818,44.004), point3(-45.376,1664.818,45.205), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-45.376,1664.818,45.205), point3(-41.093,1664.818,45.214), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-41.091,1664.818,44.285), point3(-36.354,1664.818,44.296), point3(-41.093,1664.818,45.21), material_s1));
    world.add(make_shared<triangle>(point3(-41.093,1664.818,45.214), point3(-36.354,1664.818,44.296), point3(-54.017,1664.818,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-36.372,1664.818,52.200), point3(-49.615,1664.818,52.078), point3(-36.354,1664.818,44.30), material_s1));
    world.add(make_shared<triangle>(point3(-49.615,1664.818,52.078), point3(-49.595,1664.818,49.907), point3(-36.354,1664.818,44.30), material_s1));
    world.add(make_shared<triangle>(point3(-36.354,1664.818,44.296), point3(-49.595,1664.818,49.907), point3(-54.017,1664.818,49.87), material_s1));

    // building0001
    world.add(make_shared<triangle>(point3(-37.486,1652.930,61.679), point3(-54.072,1652.930,61.526), point3(-54.072,1671.523,61.53), material_s1));
    world.add(make_shared<triangle>(point3(-37.486,1652.930,61.679), point3(-54.072,1671.523,61.526), point3(-37.486,1671.523,61.68), material_s1));
    world.add(make_shared<triangle>(point3(-54.072,1652.930,61.526), point3(-54.125,1652.930,61.526), point3(-54.125,1671.523,61.53), material_s1));
    world.add(make_shared<triangle>(point3(-54.072,1652.930,61.526), point3(-54.125,1671.523,61.526), point3(-54.072,1671.523,61.53), material_s1));
    world.add(make_shared<triangle>(point3(-54.125,1652.930,61.526), point3(-54.124,1652.930,61.465), point3(-54.124,1671.523,61.46), material_s1));
    world.add(make_shared<triangle>(point3(-54.125,1652.930,61.526), point3(-54.124,1671.523,61.465), point3(-54.125,1671.523,61.53), material_s1));
    world.add(make_shared<triangle>(point3(-54.124,1652.930,61.465), point3(-54.106,1652.930,59.441), point3(-54.106,1671.523,59.44), material_s1));
    world.add(make_shared<triangle>(point3(-54.124,1652.930,61.465), point3(-54.106,1671.523,59.441), point3(-54.124,1671.523,61.46), material_s1));
    world.add(make_shared<triangle>(point3(-54.106,1652.930,59.441), point3(-54.017,1652.930,49.866), point3(-54.017,1671.523,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-54.106,1652.930,59.441), point3(-54.017,1671.523,49.866), point3(-54.106,1671.523,59.44), material_s1));
    world.add(make_shared<triangle>(point3(-54.017,1652.930,49.866), point3(-49.595,1652.930,49.907), point3(-49.595,1671.523,49.91), material_s1));
    world.add(make_shared<triangle>(point3(-54.017,1652.930,49.866), point3(-49.595,1671.523,49.907), point3(-54.017,1671.523,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-49.595,1652.930,49.907), point3(-49.615,1652.930,52.078), point3(-49.615,1671.523,52.08), material_s1));
    world.add(make_shared<triangle>(point3(-49.595,1652.930,49.907), point3(-49.615,1671.523,52.078), point3(-49.595,1671.523,49.91), material_s1));
    world.add(make_shared<triangle>(point3(-49.615,1652.930,52.078), point3(-36.372,1652.930,52.200), point3(-36.372,1671.523,52.20), material_s1));
    world.add(make_shared<triangle>(point3(-49.615,1652.930,52.078), point3(-36.372,1671.523,52.200), point3(-49.615,1671.523,52.08), material_s1));
    world.add(make_shared<triangle>(point3(-36.372,1652.930,52.200), point3(-35.956,1652.930,52.204), point3(-35.956,1671.523,52.20), material_s1));
    world.add(make_shared<triangle>(point3(-36.372,1652.930,52.200), point3(-35.956,1671.523,52.204), point3(-36.372,1671.523,52.20), material_s1));
    world.add(make_shared<triangle>(point3(-35.956,1652.930,52.204), point3(-36.044,1652.930,61.693), point3(-36.044,1671.523,61.69), material_s1));
    world.add(make_shared<triangle>(point3(-35.956,1652.930,52.204), point3(-36.044,1671.523,61.693), point3(-35.956,1671.523,52.20), material_s1));
    world.add(make_shared<triangle>(point3(-36.044,1652.930,61.693), point3(-37.486,1652.930,61.679), point3(-37.486,1671.523,61.68), material_s1));
    world.add(make_shared<triangle>(point3(-36.044,1652.930,61.693), point3(-37.486,1671.523,61.679), point3(-36.044,1671.523,61.69), material_s1));
    world.add(make_shared<triangle>(point3(-37.486,1671.523,61.679), point3(-54.072,1671.523,61.526), point3(-36.044,1671.523,61.69), material_s1));
    world.add(make_shared<triangle>(point3(-54.125,1671.523,61.526), point3(-54.124,1671.523,61.465), point3(-54.072,1671.523,61.53), material_s1));
    world.add(make_shared<triangle>(point3(-54.072,1671.523,61.526), point3(-54.124,1671.523,61.465), point3(-36.044,1671.523,61.69), material_s1));
    world.add(make_shared<triangle>(point3(-54.124,1671.523,61.465), point3(-54.106,1671.523,59.441), point3(-36.044,1671.523,61.69), material_s1));
    world.add(make_shared<triangle>(point3(-54.106,1671.523,59.441), point3(-54.017,1671.523,49.866), point3(-36.044,1671.523,61.69), material_s1));
    world.add(make_shared<triangle>(point3(-49.595,1671.523,49.907), point3(-49.615,1671.523,52.078), point3(-54.017,1671.523,49.87), material_s1));
    world.add(make_shared<triangle>(point3(-54.017,1671.523,49.866), point3(-49.615,1671.523,52.078), point3(-36.044,1671.523,61.69), material_s1));
    world.add(make_shared<triangle>(point3(-49.615,1671.523,52.078), point3(-36.372,1671.523,52.200), point3(-36.044,1671.523,61.69), material_s1));
    world.add(make_shared<triangle>(point3(-36.372,1671.523,52.200), point3(-35.956,1671.523,52.204), point3(-36.044,1671.523,61.69), material_s1));

    // building0002
    world.add(make_shared<triangle>(point3(-53.900,1652.930,106.079), point3(-53.785,1652.930,92.156), point3(-53.785,1667.561,92.16), material_s1));
    world.add(make_shared<triangle>(point3(-53.900,1652.930,106.079), point3(-53.785,1667.561,92.156), point3(-53.900,1667.561,106.08), material_s1));
    world.add(make_shared<triangle>(point3(-53.785,1652.930,92.156), point3(-53.774,1652.930,90.870), point3(-53.774,1667.561,90.87), material_s1));
    world.add(make_shared<triangle>(point3(-53.785,1652.930,92.156), point3(-53.774,1667.561,90.870), point3(-53.785,1667.561,92.16), material_s1));
    world.add(make_shared<triangle>(point3(-53.774,1652.930,90.870), point3(-65.300,1652.930,90.880), point3(-65.300,1667.561,90.88), material_s1));
    world.add(make_shared<triangle>(point3(-53.774,1652.930,90.870), point3(-65.300,1667.561,90.880), point3(-53.774,1667.561,90.87), material_s1));
    world.add(make_shared<triangle>(point3(-65.300,1652.930,90.880), point3(-65.313,1652.930,77.036), point3(-65.313,1667.561,77.04), material_s1));
    world.add(make_shared<triangle>(point3(-65.300,1652.930,90.880), point3(-65.313,1667.561,77.036), point3(-65.300,1667.561,90.88), material_s1));
    world.add(make_shared<triangle>(point3(-65.313,1652.930,77.036), point3(-64.023,1652.930,77.035), point3(-64.023,1667.561,77.03), material_s1));
    world.add(make_shared<triangle>(point3(-65.313,1652.930,77.036), point3(-64.023,1667.561,77.035), point3(-65.313,1667.561,77.04), material_s1));
    world.add(make_shared<triangle>(point3(-64.023,1652.930,77.035), point3(-54.058,1652.930,77.026), point3(-54.058,1667.561,77.03), material_s1));
    world.add(make_shared<triangle>(point3(-64.023,1652.930,77.035), point3(-54.058,1667.561,77.026), point3(-64.023,1667.561,77.03), material_s1));
    world.add(make_shared<triangle>(point3(-54.058,1652.930,77.026), point3(-54.072,1652.930,61.526), point3(-54.072,1667.561,61.53), material_s1));
    world.add(make_shared<triangle>(point3(-54.058,1652.930,77.026), point3(-54.072,1667.561,61.526), point3(-54.058,1667.561,77.03), material_s1));
    world.add(make_shared<triangle>(point3(-54.072,1652.930,61.526), point3(-37.486,1652.930,61.679), point3(-37.486,1667.561,61.68), material_s1));
    world.add(make_shared<triangle>(point3(-54.072,1652.930,61.526), point3(-37.486,1667.561,61.679), point3(-54.072,1667.561,61.53), material_s1));
    world.add(make_shared<triangle>(point3(-37.486,1652.930,61.679), point3(-37.445,1652.930,106.215), point3(-37.445,1667.561,106.22), material_s1));
    world.add(make_shared<triangle>(point3(-37.486,1652.930,61.679), point3(-37.445,1667.561,106.215), point3(-37.486,1667.561,61.68), material_s1));
    world.add(make_shared<triangle>(point3(-37.445,1652.930,106.215), point3(-53.900,1652.930,106.079), point3(-53.900,1667.561,106.08), material_s1));
    world.add(make_shared<triangle>(point3(-37.445,1652.930,106.215), point3(-53.900,1667.561,106.079), point3(-37.445,1667.561,106.22), material_s1));
    world.add(make_shared<triangle>(point3(-53.900,1667.561,106.079), point3(-53.785,1667.561,92.156), point3(-37.445,1667.561,106.22), material_s1));
    world.add(make_shared<triangle>(point3(-53.785,1667.561,92.156), point3(-53.774,1667.561,90.870), point3(-37.445,1667.561,106.22), material_s1));
    world.add(make_shared<triangle>(point3(-65.300,1667.561,90.880), point3(-65.313,1667.561,77.036), point3(-53.774,1667.561,90.87), material_s1));
    world.add(make_shared<triangle>(point3(-53.774,1667.561,90.870), point3(-65.313,1667.561,77.036), point3(-37.445,1667.561,106.22), material_s1));
    world.add(make_shared<triangle>(point3(-65.313,1667.561,77.036), point3(-64.023,1667.561,77.035), point3(-37.445,1667.561,106.22), material_s1));
    world.add(make_shared<triangle>(point3(-64.023,1667.561,77.035), point3(-54.058,1667.561,77.026), point3(-37.445,1667.561,106.22), material_s1));
    world.add(make_shared<triangle>(point3(-54.058,1667.561,77.026), point3(-54.072,1667.561,61.526), point3(-37.445,1667.561,106.22), material_s1));
    world.add(make_shared<triangle>(point3(-54.072,1667.561,61.526), point3(-37.486,1667.561,61.679), point3(-37.445,1667.561,106.22), material_s1));

    // building0003
    world.add(make_shared<triangle>(point3(-53.900,1652.930,106.079), point3(-37.445,1652.930,106.215), point3(-37.445,1671.523,106.22), material_s1));
    world.add(make_shared<triangle>(point3(-53.900,1652.930,106.079), point3(-37.445,1671.523,106.215), point3(-53.900,1671.523,106.08), material_s1));
    world.add(make_shared<triangle>(point3(-37.445,1652.930,106.215), point3(-35.739,1652.930,106.229), point3(-35.739,1671.523,106.23), material_s1));
    world.add(make_shared<triangle>(point3(-37.445,1652.930,106.215), point3(-35.739,1671.523,106.229), point3(-37.445,1671.523,106.22), material_s1));
    world.add(make_shared<triangle>(point3(-35.739,1652.930,106.229), point3(-35.818,1652.930,115.670), point3(-35.818,1671.523,115.67), material_s1));
    world.add(make_shared<triangle>(point3(-35.739,1652.930,106.229), point3(-35.818,1671.523,115.670), point3(-35.739,1671.523,106.23), material_s1));
    world.add(make_shared<triangle>(point3(-35.818,1652.930,115.670), point3(-36.292,1652.930,115.666), point3(-36.292,1671.523,115.67), material_s1));
    world.add(make_shared<triangle>(point3(-35.818,1652.930,115.670), point3(-36.292,1671.523,115.666), point3(-35.818,1671.523,115.67), material_s1));
    world.add(make_shared<triangle>(point3(-36.292,1652.930,115.666), point3(-53.979,1652.930,115.520), point3(-53.979,1671.523,115.52), material_s1));
    world.add(make_shared<triangle>(point3(-36.292,1652.930,115.666), point3(-53.979,1671.523,115.520), point3(-36.292,1671.523,115.67), material_s1));
    world.add(make_shared<triangle>(point3(-53.979,1652.930,115.520), point3(-53.913,1652.930,107.596), point3(-53.913,1671.523,107.60), material_s1));
    world.add(make_shared<triangle>(point3(-53.979,1652.930,115.520), point3(-53.913,1671.523,107.596), point3(-53.979,1671.523,115.52), material_s1));
    world.add(make_shared<triangle>(point3(-53.913,1652.930,107.596), point3(-53.900,1652.930,106.079), point3(-53.900,1671.523,106.08), material_s1));
    world.add(make_shared<triangle>(point3(-53.913,1652.930,107.596), point3(-53.900,1671.523,106.079), point3(-53.913,1671.523,107.60), material_s1));
    world.add(make_shared<triangle>(point3(-53.900,1671.523,106.079), point3(-37.445,1671.523,106.215), point3(-53.913,1671.523,107.60), material_s1));
    world.add(make_shared<triangle>(point3(-37.445,1671.523,106.215), point3(-35.739,1671.523,106.229), point3(-53.913,1671.523,107.60), material_s1));
    world.add(make_shared<triangle>(point3(-35.739,1671.523,106.229), point3(-35.818,1671.523,115.670), point3(-53.913,1671.523,107.60), material_s1));
    world.add(make_shared<triangle>(point3(-35.818,1671.523,115.670), point3(-36.292,1671.523,115.666), point3(-53.913,1671.523,107.60), material_s1));
    world.add(make_shared<triangle>(point3(-36.292,1671.523,115.666), point3(-53.979,1671.523,115.520), point3(-53.913,1671.523,107.60), material_s1));

    // building0004
    world.add(make_shared<triangle>(point3(-89.662,1652.930,105.759), point3(-60.785,1652.930,105.878), point3(-60.785,1664.818,105.88), material_s1));
    world.add(make_shared<triangle>(point3(-89.662,1652.930,105.759), point3(-60.785,1664.818,105.878), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-60.785,1652.930,105.878), point3(-56.262,1652.930,105.896), point3(-56.262,1664.818,105.90), material_s1));
    world.add(make_shared<triangle>(point3(-60.785,1652.930,105.878), point3(-56.262,1664.818,105.896), point3(-60.785,1664.818,105.88), material_s1));
    world.add(make_shared<triangle>(point3(-56.262,1652.930,105.896), point3(-56.269,1652.930,107.586), point3(-56.269,1664.818,107.59), material_s1));
    world.add(make_shared<triangle>(point3(-56.262,1652.930,105.896), point3(-56.269,1664.818,107.586), point3(-56.262,1664.818,105.90), material_s1));
    world.add(make_shared<triangle>(point3(-56.269,1652.930,107.586), point3(-54.736,1652.930,107.592), point3(-54.736,1664.818,107.59), material_s1));
    world.add(make_shared<triangle>(point3(-56.269,1652.930,107.586), point3(-54.736,1664.818,107.592), point3(-56.269,1664.818,107.59), material_s1));
    world.add(make_shared<triangle>(point3(-54.736,1652.930,107.592), point3(-53.913,1652.930,107.596), point3(-53.913,1664.818,107.60), material_s1));
    world.add(make_shared<triangle>(point3(-54.736,1652.930,107.592), point3(-53.913,1664.818,107.596), point3(-54.736,1664.818,107.59), material_s1));
    world.add(make_shared<triangle>(point3(-53.913,1652.930,107.596), point3(-53.979,1652.930,115.520), point3(-53.979,1664.818,115.52), material_s1));
    world.add(make_shared<triangle>(point3(-53.913,1652.930,107.596), point3(-53.979,1664.818,115.520), point3(-53.913,1664.818,107.60), material_s1));
    world.add(make_shared<triangle>(point3(-53.979,1652.930,115.520), point3(-36.292,1652.930,115.666), point3(-36.292,1664.818,115.67), material_s1));
    world.add(make_shared<triangle>(point3(-53.979,1652.930,115.520), point3(-36.292,1664.818,115.666), point3(-53.979,1664.818,115.52), material_s1));
    world.add(make_shared<triangle>(point3(-36.292,1652.930,115.666), point3(-36.324,1652.930,123.549), point3(-36.324,1664.818,123.55), material_s1));
    world.add(make_shared<triangle>(point3(-36.292,1652.930,115.666), point3(-36.324,1664.818,123.549), point3(-36.292,1664.818,115.67), material_s1));
    world.add(make_shared<triangle>(point3(-36.324,1652.930,123.549), point3(-41.136,1652.930,123.529), point3(-41.136,1664.818,123.53), material_s1));
    world.add(make_shared<triangle>(point3(-36.324,1652.930,123.549), point3(-41.136,1664.818,123.529), point3(-36.324,1664.818,123.55), material_s1));
    world.add(make_shared<triangle>(point3(-41.136,1652.930,123.529), point3(-41.132,1652.930,122.447), point3(-41.132,1664.818,122.45), material_s1));
    world.add(make_shared<triangle>(point3(-41.136,1652.930,123.529), point3(-41.132,1664.818,122.447), point3(-41.136,1664.818,123.53), material_s1));
    world.add(make_shared<triangle>(point3(-41.132,1652.930,122.447), point3(-45.325,1652.930,122.430), point3(-45.325,1664.818,122.43), material_s1));
    world.add(make_shared<triangle>(point3(-41.132,1652.930,122.447), point3(-45.325,1664.818,122.430), point3(-41.132,1664.818,122.45), material_s1));
    world.add(make_shared<triangle>(point3(-45.325,1652.930,122.430), point3(-45.329,1652.930,123.516), point3(-45.329,1664.818,123.52), material_s1));
    world.add(make_shared<triangle>(point3(-45.325,1652.930,122.430), point3(-45.329,1664.818,123.516), point3(-45.325,1664.818,122.43), material_s1));
    world.add(make_shared<triangle>(point3(-45.329,1652.930,123.516), point3(-50.204,1652.930,123.496), point3(-50.204,1664.818,123.50), material_s1));
    world.add(make_shared<triangle>(point3(-45.329,1652.930,123.516), point3(-50.204,1664.818,123.496), point3(-45.329,1664.818,123.52), material_s1));
    world.add(make_shared<triangle>(point3(-50.204,1652.930,123.496), point3(-50.193,1652.930,120.793), point3(-50.193,1664.818,120.79), material_s1));
    world.add(make_shared<triangle>(point3(-50.204,1652.930,123.496), point3(-50.193,1664.818,120.793), point3(-50.204,1664.818,123.50), material_s1));
    world.add(make_shared<triangle>(point3(-50.193,1652.930,120.793), point3(-85.921,1652.930,120.646), point3(-85.921,1664.818,120.65), material_s1));
    world.add(make_shared<triangle>(point3(-50.193,1652.930,120.793), point3(-85.921,1664.818,120.646), point3(-50.193,1664.818,120.79), material_s1));
    world.add(make_shared<triangle>(point3(-85.921,1652.930,120.646), point3(-85.917,1652.930,119.551), point3(-85.917,1664.818,119.55), material_s1));
    world.add(make_shared<triangle>(point3(-85.921,1652.930,120.646), point3(-85.917,1664.818,119.551), point3(-85.921,1664.818,120.65), material_s1));
    world.add(make_shared<triangle>(point3(-85.917,1652.930,119.551), point3(-88.761,1652.930,119.539), point3(-88.761,1664.818,119.54), material_s1));
    world.add(make_shared<triangle>(point3(-85.917,1652.930,119.551), point3(-88.761,1664.818,119.539), point3(-85.917,1664.818,119.55), material_s1));
    world.add(make_shared<triangle>(point3(-88.761,1652.930,119.539), point3(-88.756,1652.930,118.310), point3(-88.756,1664.818,118.31), material_s1));
    world.add(make_shared<triangle>(point3(-88.761,1652.930,119.539), point3(-88.756,1664.818,118.310), point3(-88.761,1664.818,119.54), material_s1));
    world.add(make_shared<triangle>(point3(-88.756,1652.930,118.310), point3(-104.579,1652.930,118.245), point3(-104.579,1664.818,118.25), material_s1));
    world.add(make_shared<triangle>(point3(-88.756,1652.930,118.310), point3(-104.579,1664.818,118.245), point3(-88.756,1664.818,118.31), material_s1));
    world.add(make_shared<triangle>(point3(-104.579,1652.930,118.245), point3(-104.528,1652.930,105.863), point3(-104.528,1664.818,105.86), material_s1));
    world.add(make_shared<triangle>(point3(-104.579,1652.930,118.245), point3(-104.528,1664.818,105.863), point3(-104.579,1664.818,118.25), material_s1));
    world.add(make_shared<triangle>(point3(-104.528,1652.930,105.863), point3(-94.577,1652.930,105.904), point3(-94.577,1664.818,105.90), material_s1));
    world.add(make_shared<triangle>(point3(-104.528,1652.930,105.863), point3(-94.577,1664.818,105.904), point3(-104.528,1664.818,105.86), material_s1));
    world.add(make_shared<triangle>(point3(-94.577,1652.930,105.904), point3(-94.572,1652.930,104.759), point3(-94.572,1664.818,104.76), material_s1));
    world.add(make_shared<triangle>(point3(-94.577,1652.930,105.904), point3(-94.572,1664.818,104.759), point3(-94.577,1664.818,105.90), material_s1));
    world.add(make_shared<triangle>(point3(-94.572,1652.930,104.759), point3(-89.657,1652.930,104.779), point3(-89.657,1664.818,104.78), material_s1));
    world.add(make_shared<triangle>(point3(-94.572,1652.930,104.759), point3(-89.657,1664.818,104.779), point3(-94.572,1664.818,104.76), material_s1));
    world.add(make_shared<triangle>(point3(-89.657,1652.930,104.779), point3(-89.662,1652.930,105.759), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-89.657,1652.930,104.779), point3(-89.662,1664.818,105.759), point3(-89.657,1664.818,104.78), material_s1));
    world.add(make_shared<triangle>(point3(-60.785,1664.818,105.878), point3(-56.262,1664.818,105.896), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-56.262,1664.818,105.896), point3(-56.269,1664.818,107.586), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-54.736,1664.818,107.592), point3(-53.913,1664.818,107.596), point3(-56.269,1664.818,107.59), material_s1));
    world.add(make_shared<triangle>(point3(-53.913,1664.818,107.596), point3(-53.979,1664.818,115.520), point3(-56.269,1664.818,107.59), material_s1));
    world.add(make_shared<triangle>(point3(-56.269,1664.818,107.586), point3(-53.979,1664.818,115.520), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-36.292,1664.818,115.666), point3(-36.324,1664.818,123.549), point3(-53.979,1664.818,115.52), material_s1));
    world.add(make_shared<triangle>(point3(-53.979,1664.818,115.520), point3(-36.324,1664.818,123.549), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-41.136,1664.818,123.529), point3(-41.132,1664.818,122.447), point3(-36.324,1664.818,123.55), material_s1));
    world.add(make_shared<triangle>(point3(-36.324,1664.818,123.549), point3(-41.132,1664.818,122.447), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-41.132,1664.818,122.447), point3(-45.325,1664.818,122.430), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-45.329,1664.818,123.516), point3(-50.204,1664.818,123.496), point3(-45.325,1664.818,122.43), material_s1));
    world.add(make_shared<triangle>(point3(-50.204,1664.818,123.496), point3(-50.193,1664.818,120.793), point3(-45.325,1664.818,122.43), material_s1));
    world.add(make_shared<triangle>(point3(-45.325,1664.818,122.430), point3(-50.193,1664.818,120.793), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-85.921,1664.818,120.646), point3(-85.917,1664.818,119.551), point3(-50.193,1664.818,120.79), material_s1));
    world.add(make_shared<triangle>(point3(-50.193,1664.818,120.793), point3(-85.917,1664.818,119.551), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-88.761,1664.818,119.539), point3(-88.756,1664.818,118.310), point3(-85.917,1664.818,119.55), material_s1));
    world.add(make_shared<triangle>(point3(-85.917,1664.818,119.551), point3(-88.756,1664.818,118.310), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-88.756,1664.818,118.310), point3(-104.579,1664.818,118.245), point3(-89.662,1664.818,105.76), material_s1));
    world.add(make_shared<triangle>(point3(-89.662,1664.818,105.759), point3(-104.579,1664.818,118.245), point3(-89.657,1664.818,104.78), material_s1));
    world.add(make_shared<triangle>(point3(-104.528,1664.818,105.863), point3(-94.577,1664.818,105.904), point3(-104.579,1664.818,118.25), material_s1));
    world.add(make_shared<triangle>(point3(-104.579,1664.818,118.245), point3(-94.577,1664.818,105.904), point3(-89.657,1664.818,104.78), material_s1));
    world.add(make_shared<triangle>(point3(-94.577,1664.818,105.904), point3(-94.572,1664.818,104.759), point3(-89.657,1664.818,104.78), material_s1));
    world.add(make_shared<triangle>(point3(0.000,0.000,0.000), point3(68.911,0.000,79.557), point3(0.000,0.000,79.56), material_s1));
    world.add(make_shared<triangle>(point3(0.000,0.000,0.000), point3(68.911,0.000,0.000), point3(68.911,0.000,79.56), material_s1));


    
    return world;
}