//
// Created by Thierry Backes on 19/04/18.
//

#include "Vec3.h"

class Ray{
public:
    Ray(): orig(0),dir(0,0,1),tMin(0.1),tMax(1000){};
    Ray(const Vec3f &o, const Vec3f &d):orig(o),dir(d),tMin(0.1), tMax(1000){};

    Vec3f orig;
    Vec3f dir;

    float tMin, tMax;
};