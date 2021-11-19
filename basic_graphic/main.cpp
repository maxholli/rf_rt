#include "headers/rtweekend.h"

#include "headers/color.h"
#include "headers/hittable_list.h"
#include "headers/sphere.h"
#include "headers/camera.h"
#include "headers/material.h"
#include "headers/aarect.h"
#include "headers/box.h"

#include <iostream>
// #include <stdlib.h>
// #include <time.h>

// notes

// random_in_unit_sphere seems like it should be based on the size of the sphere not limited to 1 unit


// another way to think of this is light source?
color ray_color(const ray& r, const color& background, const hittable& world, int depth)
{   
    // if we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);
    
    hit_record rec;
    // if the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, inifinity, rec)) 
        return background;

    
    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, background, world, depth-1);
}

hittable_list three_marbles_worship() 
{
    hittable_list world;
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2));
    auto material_r1 = make_shared<diffuse_light>(color(4, 4, 4));


    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    world.add(make_shared<xy_rect>(-1, 1, 1, 3, -5, material_r1));
    return world;
}

hittable_list cornell_box() {
    hittable_list objects;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

    objects.add(make_shared<box>(point3(130, 0, 65), point3(295, 165, 230), white));
    objects.add(make_shared<box>(point3(265, 0, 295), point3(430, 330, 460), white));

    return objects;
}

int main()
{
    srand(time(NULL));

    // image
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 1000;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    int samples_per_pixel = 100;
    const int max_depth = 20;
    // World
    hittable_list world;
    point3 lookfrom;
    point3 lookat;
    double vfov;
    

    color background = color(0.70, 0.80, 1.00); // default light blue
    // color background = color(0, 0, 0);

    switch (0)
    {
        case 0:
            world = three_marbles_worship();
            aspect_ratio = 16.0 / 9.0;
            image_width = 400;
            image_height = static_cast<int>(image_width / aspect_ratio);
            samples_per_pixel = 50;
            background = color(0, 0, 0);
            lookfrom = point3(-0.5,2,2);
            lookat = point3(0,0,-1);
            vfov = 90.0;
            break;
        case 1:
            world = cornell_box();
            aspect_ratio = 1.0;
            image_width = 600;
            samples_per_pixel = 50;
            background = color(0,0,0);
            lookfrom = point3(278, 278, -800);
            lookat = point3(278, 278, 0);
            vfov = 40.0;
            break;
    }



    // camera
    camera cam(lookfrom, lookat, vec3(0,1,0), vfov, aspect_ratio);
    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color(0,0,0);
            for (int s=0; s < samples_per_pixel; s++)
            {
                auto u = (i+random_double()) / (image_width-1);
                auto v = (j+random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, background, world, max_depth);                
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}