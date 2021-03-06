//
// Created by Thierry Backes on 21/12/17.
//

#ifndef INAWEEKEND_SPHERE_H
#define INAWEEKEND_SPHERE_H

#include "hitable.h"

class sphere: public hitable{
public:
    sphere(){}
    sphere(vec3 cen, float r,material *m):center(cen),radius(r),mat_ptr(m){};
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    vec3 center;
    float radius;
    material *mat_ptr;

    ~sphere(){
        free(mat_ptr);
    }
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(),r.direction());
    float b = dot(oc,r.direction());
    float c = dot(oc,oc)-radius*radius;
    float discriminant = b*b-a*c;
    if(discriminant > 0){
        float tmp = (-b-sqrtf(b*b-a*c))/(a);
        if(tmp < t_max && tmp > t_min){
            rec.t = tmp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p-center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        tmp = ((-b + sqrtf(b * b - a * c)) / a);
        if(tmp < t_max && tmp > t_min){
            rec.t = tmp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p-center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

#endif //INAWEEKEND_SPHERE_H
