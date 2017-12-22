//
// Created by Thierry Backes on 21/12/17.
//

#ifndef INAWEEKEND_RAY_H
#define INAWEEKEND_RAY_H

#include "vec3.h"

class ray{
public:
    ray() = default;
    ray(const vec3& a, const vec3 &b):A(a),B(b){};
    vec3 origin()const{return A;}
    vec3 direction()const{return B;}
    vec3 point_at_parameter(float t)const{return A+t*B;}

    vec3 A;
    vec3 B;
};

#endif //INAWEEKEND_RAY_H
