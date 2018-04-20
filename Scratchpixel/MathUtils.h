//
// Created by Thierry Backes on 27/03/18.
//

#ifndef SCRATCHPIXEL_MATHUTILS_H
#define SCRATCHPIXEL_MATHUTILS_H


#include <algorithm>
#include "Vec3.h"
/**
 * Numerically stable quadratic equation solver
 */
bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
{
    float discr = b * b - 4 * a * c;
    if (discr < 0) return false;
    else if (discr == 0){
        x0 = x1 = static_cast<float>(- 0.5 * b / a);
    } else {
        auto q = static_cast<float>((b > 0) ?
                                    -0.5 * (b + std::sqrt(discr)) :
                                    -0.5 * (b - std::sqrt(discr)));
        x0 = q / a;
        x1 = c / q; //wtf?
    }

    return true;
}

inline float clamp(const float &lo, const float &hi, const float &v)
{
    return std::max(lo, std::min(hi, v));
}

inline float deg2rad(const float &deg)
{
    return static_cast<float>(deg * M_PI / 180);
}

inline Vec3f mix(const Vec3f &a, const Vec3f& b, const float &mixValue)
{
    return a * (1 - mixValue) + b * mixValue;
}

/*
template<typename T>
Vec3<T> sphericalToCartesian(const T &theta, const T &phi)
{
    return Vec3<T>(cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta));
};

template<typename T>
inline T sphericalTheta(const Vec3<T> &v)
{
    return acos(clamp<T>(v[2], -1, 1));
}

template<typename T>
inline T sphericalPhi(const Vec3<T> &v)
{
    T p = atan2(v[1], v[0]);
    return (p < 0) ? p + 2 * M_PI : p;
}

template<typename T> inline T cosTheta(const Vec3<T> &w) { return w.z; }


template<typename T>
inline T sinTheta2(const Vec3<T> &w)
{
    return std::max(T(0), 1 - cosTheta(w) * cosTheta(w));
}

template<typename T>
inline T sinTheta(const Vec3<T> &w)
{
    return sqrt(sinTheta2(w));
}

template<typename T>
inline T cosPhi(const Vec3<T> &w)
{
    T sintheta = sinTheta(w);
    if (sintheta == 0) return 1;
    return clamp<T>(w.x / sintheta, -1, 1);
}

template<typename T>
inline T sinPhi(const Vec3<T> &w)
{
    T sintheta = sinTheta(w);
    if (sintheta == 0) return 0;
    return clamp<T>(w.y / sintheta, -1, 1);
} */
#endif //SCRATCHPIXEL_MATHUTILS_H
