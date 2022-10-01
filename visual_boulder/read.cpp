#include "headers/rtweekend.h"
#include "headers/color.h"
#include "headers/hittable_list.h"
#include "headers/sphere.h"
#include "headers/camera.h"
#include "headers/material.h"
#include "headers/bounce_hist.h"
#include "headers/triangle.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int read_world_from_file(hittable_list& world, std::string filename)
{
    // ground
    auto material_s2 = make_shared<lambertian>(color(0.37, 0.37, 0.37));

    // buildings
    auto material_s1 = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    
    std::fstream newfile;
    newfile.open(filename, std::ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) //checking whether the file is open
    { 
        std::string tp;
        while(std::getline(newfile, tp)){ //read data from file object and put it into string.
            // world.add(make_shared<triangle>(point3(-54.106,1652.930,59.441), point3(-56.532,1652.930,62.173), point3(-56.532,1664.818,62.17), material_s1));
            std::regex str_expr (".*world\\.add.*point3\\((.*),(.*),(.*)\\), point3\\((.*),(.*),(.*)\\), point3\\((.*),(.*),(.*)\\), (.*)\\)\\);.*");
            std::smatch sm;
            if (std::regex_match(tp, sm, str_expr))
            {
                // std::cout << "we have a match\n";
                // std::cout << sm.size() << '\n';
                // std::cout << sm[0] << '\n';
                // std::cout << sm[1] << '\n';
                // std::cout << sm[2] << '\n';
                // std::cout << sm[3] << '\n';
                // std::cout << sm[4] << '\n';
                // std::cout << sm[5] << '\n';
                // std::cout << sm[6] << '\n';
                // std::cout << sm[7] << '\n';
                // std::cout << sm[8] << '\n';
                // std::cout << sm[9] << '\n';
                // std::cout << sm[10] << '\n';
                if (sm[10] == "material_s1")
                {
                    world.add(make_shared<triangle>(point3(std::stod(sm[1]),std::stod(sm[2]),std::stod(sm[3])), point3(std::stod(sm[4]),std::stod(sm[5]),std::stod(sm[6])), point3(std::stod(sm[7]),std::stod(sm[8]),std::stod(sm[9])), material_s1));
                } else if (sm[10] == "material_s2")
                {
                    world.add(make_shared<triangle>(point3(std::stod(sm[1]),std::stod(sm[2]),std::stod(sm[3])), point3(std::stod(sm[4]),std::stod(sm[5]),std::stod(sm[6])), point3(std::stod(sm[7]),std::stod(sm[8]),std::stod(sm[9])), material_s2));
                } else 
                {
                std::cout << "ERROR: unknown material "  << sm[10] << '\n';
                }
            } 
            else {
                std::cout << "ERROR: THE LINE WASN'T A MATCH" << '\n' << tp << '\n';
            }
            
            
        }
        newfile.close(); //close the file object.
    }
    return 1;
}

int main()
{
    hittable_list world;

    read_world_from_file(world, "worlds/full_summer_12m.h");
    
    std::cout << world.objects.size() << '\n';
}