//
// Created by Thierry Backes on 22/03/18.
//

#ifndef SCRATCHPIXEL_VEC3_H
#define SCRATCHPIXEL_VEC3_H

#include <cmath>
#include <cstdint>
#include <iostream>


template<typename T>
class Vec3 {
public:
    Vec3():x{},y{},z{} {}
    explicit Vec3(const T &val): x(val),y(val),z(val){}
    Vec3(T xx, T yy, T zz): x(xx), y(yy), z(zz){}
    T x, y, z;

    T length();
    Vec3<T> &normalize();
    T dot(const Vec3<T> &v) const;
    Vec3<T> cross(const Vec3<T> &v) const;


    Vec3<T> operator + (const Vec3<T> &v) const
    { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
    Vec3<T> operator - (const Vec3<T> &v) const
    { return Vec3<T>(x - v.x, y - v.y, z - v.z); }

    Vec3 operator - () const
    { return Vec3(-x, -y, -z);}

    Vec3 operator * (const T &r) const
    { return Vec3(x * r, y * r, z * r); }

    Vec3 operator * (const Vec3 &v) const
    { return Vec3(x * v.x, y * v.y, z * v.z); }

    const T& operator [] (uint8_t i) const { return (&x)[i]; }
    T& operator [] (uint8_t i) { return (&x)[i]; }

    friend std::ostream& operator << (std::ostream &s, const Vec3<T> &v)
    {
        return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ')';
    }

    friend Vec3 operator * (const T &r, const Vec3 &v)
    { return Vec3<T>(v.x * r, v.y * r, v.z * r); }

};
typedef Vec3<float> Vec3f;
typedef Vec3<float> Point3f;


template<typename T>
T Vec3<T>::length() {
    return sqrt(x * x + y * y + z * z);
}

template<typename T>
Vec3<T> &Vec3<T>::normalize() {
    {
        T len = length();
        if (len > 0) {
            T invLen = 1 / len;
            x *= invLen, y *= invLen, z *= invLen;
        }
        return *this;
    }
}

template<typename T>
T Vec3<T>::dot(const Vec3<T> &v) const {
    return x * v.x + y * v.y + z * v.z;
}

template<typename T>
Vec3<T> Vec3<T>::cross(const Vec3<T> &v) const {
    return Vec3<T>(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
}



/*
//Utility functions
template<typename T>
T Vec3<T>::length(const Vec3<T> &v){
    return sqrt(x * x + y * y + z * z);
}

template<typename T>
void normalize(Vec3<T> &v){
    {
        T len = length();
        if (len > 0) {
            T invLen = 1 / len;
            x *= invLen, y *= invLen, z *= invLen;
        }
        return *this;
    }
}
 */

//template<typename T>
//T dot(const Vec3<T> &a, const Vec3<T> &b);
template<typename T>
Vec3<T> cross(const Vec3<T>  &a, const Vec3<T> &b);
#endif //SCRATCHPIXEL_VEC3_H

