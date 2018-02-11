//
// Created by Thierry Backes on 07/01/18.
//

#ifndef INONEWEEKEND_RAY_H
#define INONEWEEKEND_RAY_H

#include "vec3.h"

class ray{
public:
    ray() = default;
    ray(const Vec3 ori, const Vec3 dir):origin(ori){
        //direction = normalized(dir);
        direction = (dir);
    };

    const Vec3 &getOrigin() const {
        return origin;
    }

    const Vec3 &getDirection() const {
        return direction;
    }

    Vec3 pointAtParam(float t) const{return origin+t*direction;}

private:
    Vec3 origin;
    Vec3 direction;
};


#endif //INONEWEEKEND_RAY_H
