//
// Created by Thierry Backes on 21/12/17.
//

#ifndef INAWEEKEND_HITABLE_H
#define INAWEEKEND_HITABLE_H

#include "ray.h"

class material;

struct hit_record{
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};
#endif //INAWEEKEND_HITABLE_H
