#ifndef ISOTROPIC_ANTENNA_H
#define ISOTROPIC_ANTENNA_H

#include "rtweekend.h"

class iso_antenna
{
    public:
        iso_antenna(point3 lookfrom)
        {
            origin = lookfrom;
        }

        ray get_ray()
        {
            vec3 dir = random_unit_vector();
            return ray(origin, dir);
        }

    public:
        point3 origin;
};

#endif