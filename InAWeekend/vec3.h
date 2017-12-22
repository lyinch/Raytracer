//
// Created by Thierry Backes on 21/12/17.
//

#ifndef INAWEEKEND_VEC3_H
#define INAWEEKEND_VEC3_H


#include <cmath>
#include <iostream>

class vec3 {
public:
    vec3() = default;

    vec3(float e0, float e1, float e2){e[0] = e0; e[1] = e1; e[2] = e2;}

    /** return values for different types **/
    inline float x() const{return e[0];}
    inline float y() const{return e[1];}
    inline float z() const{return e[2];}

    inline float r() const{return e[0];}
    inline float g() const{return e[1];}
    inline float b() const{return e[2];}

    /** unary operator overloading **/
    inline const vec3& operator+() const{return *this;}
    inline vec3 operator-() const{return {-e[0],-e[1],-e[2]};}
    inline float operator[] (int i) const{return e[i];}
    inline float& operator[] (int i) {return e[i];}

    /** binary operator overloading **/
    inline vec3& operator+= (const vec3 &v);
    inline vec3& operator-= (const vec3 &v);
    inline vec3& operator*= (const vec3 &v);
    inline vec3& operator/= (const vec3 &v);
    inline vec3& operator*= (float t);
    inline vec3& operator/= (float t);

    inline float length() const{return std::sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);}
    inline float squared_length() const{return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];}
    inline void normalize();

    float e[3]{};
};


inline std::istream& operator>>(std::istream &is, vec3 &t){
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator>>(std::ostream &os, const vec3 &t){
    os << t.e[0] << " " << t.e[1] << " " <<t.e[2];
    return os;
}




inline vec3 operator+ (const vec3 &v1, const vec3 &v2){
    return {v1[0]+v2[0],v1[1]+v2[1],v1[2]+v2[2]};
}

inline vec3 operator- (const vec3 &v1, const vec3 &v2){
    return {v1[0]-v2[0],v1[1]-v2[1],v1[2]-v2[2]};
}


inline vec3 operator* (const vec3 &v1, const vec3 &v2){
    return {v1[0]*v2[0],v1[1]*v2[1],v1[2]*v2[2]};
}

inline vec3 operator/ (const vec3 &v1, const vec3 &v2){
    return {v1[0]/v2[0],v1[1]/v2[1],v1[2]/v2[2]};
}

inline vec3 operator* (float t, const vec3 &v1){
    return {t*v1[0],t*v1[1],t*v1[2]};
}

inline vec3 operator* (const vec3 &v1,float t ){
    return t*v1;
}

inline vec3 operator/ (const vec3 &vec1,float t ){
    return {vec1[0]/t,vec1[1]/t,vec1[2]/t};
}


inline float dot(const vec3 &v1, const vec3 &v2){
    return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2){
    return {v1[1]*v2[2]-v1[2]*v1[1],
            -(v1[0]*v2[2]-v1[2]*v2[0]),
            v1[0]*v2[1]-v1[1]*v2[0]};
}

vec3 &vec3::operator+=(const vec3 &v) {
    e[0] += v[0];
    e[1] += v[1];
    e[2] += v[2];
    return *this;
}
vec3 &vec3::operator-=(const vec3 &v) {
    e[0] -= v[0];
    e[1] -= v[1];
    e[2] -= v[2];
    return *this;
}

vec3 &vec3::operator/=(const vec3 &v) {
    e[0] /= v[0];
    e[1] /= v[1];
    e[2] /= v[2];
    return *this;
}

vec3 &vec3::operator*=(const vec3 &v) {
    e[0] *= v[0];
    e[1] *= v[1];
    e[2] *= v[2];
    return *this;
}


vec3 &vec3::operator/=(const float t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}



vec3 &vec3::operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}


inline void vec3::normalize(){
    float k = squared_length();
    e[0] /= k;
    e[1] /= k;
    e[2] /= k;
}

inline vec3 normalized(vec3 v){
    return v/v.length();
}



#endif //INAWEEKEND_VEC3_H
