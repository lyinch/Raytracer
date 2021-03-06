//
// Created by Thierry Backes on 22/12/17.
//

#ifndef INAWEEKEND_CAMERA_H
#define INAWEEKEND_CAMERA_H

#include "ray.h"
vec3 random_in_unit_disk(){
    vec3 p;
    do{
        p = 2.0*vec3(drand48(),drand48(),0)-vec3(1,1,0);
    }while (p.squared_length() >= 1.f);
    return p;
}


class camera{
public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist){ //vfov: top to bottom in degrees
        lens_radius = aperture/2;
        float theta = (float)(vfov*M_PI/180);
        float half_height = tanf(theta/2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = normalized(lookfrom-lookat);
        u = normalized(cross(vup,w));
        v = cross(w,u);
        lower_left_corner = origin-half_width*focus_dist*u-half_height*focus_dist*v-w*focus_dist;
        horizontal = 2*half_width*focus_dist*u;
        vertical = 2*half_height*focus_dist*v;
    }

    ray get_ray(float s, float t){
        vec3 rd = lens_radius*random_in_unit_disk();
        vec3 offset = u*rd.x()+v*rd.y();
        return ray(origin+offset,lower_left_corner+s*horizontal+t*vertical-origin-offset);
    }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u,v,w;
    float lens_radius;
};
#endif //INAWEEKEND_CAMERA_H
