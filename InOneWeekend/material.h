//
// Created by Thierry Backes on 11/02/18.
//

#ifndef INONEWEEKEND_MATERIAL_H
#define INONEWEEKEND_MATERIAL_H

#include <stdlib.h>
#include "ray.h"
#include "hitable.h"

// http://mathworld.wolfram.com/SpherePointPicking.html
Vec3 random_point_on_unit_sphere(){
    auto phi = static_cast<float>(drand48() * 2 * M_PI);
    auto u = static_cast<float>(drand48() * 2 - 1);
    float t = sqrtf(1-u*u);
    return {t*cosf(phi),t*sinf(phi),u};
}
/*
Vec3 random_point_on_unit_sphere(){
    Vec3 p;
    do{
        p = 2.0f*Vec3(drand48(),drand48(),drand48())-Vec3(1,1,1);
    }while (p.squared_length() >= 1.0);

    return  p;
}
*/

class material{
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, Vec3& attenuation, ray& scattered) const = 0;
};

class lambertian: public material{
public:
    explicit lambertian(const Vec3& a):albedo(a){};

    virtual bool scatter(const ray& r_in, const hit_record& rec, Vec3& attenuation, ray& scattered){
        Vec3 target = rec.p + rec.normal + random_point_on_unit_sphere();
        scattered = ray(rec.p,target-rec.p);
        attenuation = albedo;
        return true;
    }

    Vec3 albedo;

};
#endif //INONEWEEKEND_MATERIAL_H
