//
// Created by Thierry Backes on 19/04/18.
//

#ifndef SCRATCHPIXEL_OBJECT_H
#define SCRATCHPIXEL_OBJECT_H

#include "Vec3.h"
#include "Vec2.h"

class Object
{
public:
    Object(){
        //ToDo: Remove random color initialization
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);
        color.x = dis(gen);
        color.y = dis(gen);
        color.z = dis(gen);
    }
    virtual bool intersect(const Vec3f &orig, const Vec3f &dir, float &t) const = 0;
    virtual ~Object() = default;
    //ToDo: generalize getSurfaceData
    virtual void getSurfaceData(const Vec3f &, Vec3f &, Vec2f &) const = 0;
    Vec3f color;
};

#endif //SCRATCHPIXEL_OBJECT_H
