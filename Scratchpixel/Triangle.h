//
// Created by Thierry Backes on 20/04/18.
//

#ifndef SCRATCHPIXEL_TRIANGLE_H
#define SCRATCHPIXEL_TRIANGLE_H

#include <cmath>

#include "Object.h"
constexpr float kEpsilon = 1e-8;

class Triangle : public Object{
public:
    Triangle(const Vec3f &a,const Vec3f &b,const Vec3f &c) : v0(a), v1(b),v2(c), culling(false) {}
    Vec3f v0,v1,v2;
    bool culling;

    void getSurfaceData(const Vec3f &Phit, Vec3f &Nhit, Vec2f &tex) const override{
        //std::cout << "Called what" << std::endl;
    }


    //Möller–Trumbore Ray triangle intersection
    bool intersect(const Vec3f &orig, const Vec3f &dir, float &t) const override {
        Vec3f v0v1 = v1 - v0;
        Vec3f v0v2 = v2 - v0;
        Vec3f pvec = dir.cross(v0v2);
        float det = v0v1.dot(pvec);
        //std::cout << det << std::endl;
        if(culling) {
            if (det < kEpsilon) {
                return false;
            }

        }
        else {
            if (std::fabs(det) < kEpsilon) {
                return false;
            }
        }

        float invDet = 1 / det;

        Vec3f tvec = orig - v0;
        float u = tvec.dot(pvec) * invDet;
        if (u < 0 || u > 1) return false;

        Vec3f qvec = tvec.cross(v0v1);
        float v = dir.dot(qvec) * invDet;
        if (v < 0 || u + v > 1) return false;

        t = v0v2.dot(qvec) * invDet;
        return true;

    }


};

#endif //SCRATCHPIXEL_TRIANGLE_H
