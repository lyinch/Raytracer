//
// Created by Thierry Backes on 19/04/18.
//

#ifndef SCRATCHPIXEL_SPHERE_H
#define SCRATCHPIXEL_SPHERE_H

#include "Object.h"
#include "MathUtils.h"

class Sphere : public Object{
public:
    Sphere(const Vec3f &c, const float &r) : radius(r), radius2(r *r ), center(c) {}
    float radius, radius2;
    Vec3f center;

    void getSurfaceData(const Vec3f &Phit, Vec3f &Nhit, Vec2f &tex) const override {
        Nhit = Phit - center;
        tex.x = static_cast<float>((1 + atan2(Nhit.z, Nhit.x) / M_PI) * 0.5);
        tex.y = static_cast<float>(acosf(Nhit.y) / M_PI);
    }

    bool intersect(const Vec3f &orig, const Vec3f &dir, float &t) const override {

        float t0, t1;
        Vec3f L = orig - center;
        float a = dir.dot(dir);
        float b = 2 * dir.dot(L);
        float c = L.dot(L) - radius2;
        if (!solveQuadratic(a, b, c, t0, t1)) return false;

        if (t0 > t1) std::swap(t0, t1);
        if (t0 < 0) {
            t0 = t1;
            if (t0 < 0) return false;
        }

        t = t0;
        return true;
    }
};
#endif //SCRATCHPIXEL_SPHERE_H
