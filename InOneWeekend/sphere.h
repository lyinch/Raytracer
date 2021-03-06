//
// Created by Thierry Backes on 06/02/18.
//

#ifndef INONEWEEKEND_SPHERE_H
#define INONEWEEKEND_SPHERE_H

#include <iostream>
#include "hitable.h"

class sphere: public hitable{
public:
    sphere() = default;
    sphere(Vec3 cen, float r):center(cen),radius(r){};
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;
    Vec3 center;
    float radius;
};


bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    Vec3 originToCenter = r.getOrigin()-center;
    float a = dot(r.getDirection(),r.getDirection());
    float b = 2.f*dot(originToCenter,r.getDirection());
    float c = dot(originToCenter,originToCenter)-radius*radius;
    float discriminant = b*b-4.f*a*c;
    //std::cout << discriminant << std::endl;

    if(discriminant > 0) {
        float intersection = (-b-sqrtf(discriminant))/(2.0f*a);

        if(intersection < t_max && intersection > t_min){

            rec.t = intersection;
            rec.p = r.pointAtParam(intersection);
            rec.normal = normalized((rec.p-center)/radius);
            return true;
        }

        intersection = (-b+sqrtf(discriminant))/(2.0f*a);
        if(intersection < t_max && intersection > t_min){
            rec.t = intersection;
            rec.p = r.pointAtParam(intersection);
            rec.normal = normalized((rec.p-center)/radius);
            return true;
        }

    }

    return false;
}

#endif //INONEWEEKEND_SPHERE_H
