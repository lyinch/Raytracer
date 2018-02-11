//
// Created by Thierry Backes on 06/02/18.
//

#ifndef INONEWEEKEND_HITABLE_H
#define INONEWEEKEND_HITABLE_H

#include "ray.h"

struct hit_record{
    float t; //z coordinate of hit
    Vec3 p; //exact point of hit
    Vec3 normal;
};

class hitable{
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif //INONEWEEKEND_HITABLE_H
