//
// Created by Thierry Backes on 27/03/18.
//

#ifndef SCRATCHPIXEL_MATRIX_H
#define SCRATCHPIXEL_MATRIX_H

#include <cstdint>
#include <iomanip>
#include "Vec3.h"

template<typename T>
class Matrix44 {
public:
    Matrix44() = default;

    Matrix44 (T a, T b, T c, T d, T e, T f, T g, T h,
              T i, T j, T k, T l, T z, T n, T o, T p)
    {
        m[0][0] = a;
        m[0][1] = b;
        m[0][2] = c;
        m[0][3] = d;
        m[1][0] = e;
        m[1][1] = f;
        m[1][2] = g;
        m[1][3] = h;
        m[2][0] = i;
        m[2][1] = j;
        m[2][2] = k;
        m[2][3] = l;
        m[3][0] = z;
        m[3][1] = n;
        m[3][2] = o;
        m[3][3] = p;
    }

    const T* operator[] (uint8_t i) const {return m[i];}
    T* operator [] (uint8_t i) { return m[i]; }

    Matrix44 operator * (const Matrix44& rhs) const{
        Matrix44 mult;
        for (uint8_t i = 0; i < 4; ++i) {
            for (uint8_t j = 0; j < 4; ++j) {
                mult[i][j] = m[i][0] * rhs[0][j] +
                             m[i][1] * rhs[1][j] +
                             m[i][2] * rhs[2][j] +
                             m[i][3] * rhs[3][j];
            }
        }

        return mult;
    }
    T m[4][4] =  {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

    void multVecMatrix(const Vec3<T> &src, Vec3<T> &dst) const;
    void multDirMatrix(const Vec3<T> &src, Vec3<T> &dst) const;
    //ToDo: Definitions
    Matrix44 transpose() const;
    static void multiply(const Matrix44<T> &a, const Matrix44& b, Matrix44 &c);
    Matrix44 transposed() const;


    friend std::ostream& operator << (std::ostream &s, const Matrix44 &m)
    {
        std::ios_base::fmtflags oldFlags = s.flags();
        int width = 12; // total with of the displayed number
        s.precision(5); // control the number of displayed decimals
        s.setf (std::ios_base::fixed);

        s << "(" << std::setw (width) << m[0][0] <<
          " " << std::setw (width) << m[0][1] <<
          " " << std::setw (width) << m[0][2] <<
          " " << std::setw (width) << m[0][3] << "\n" <<

          " " << std::setw (width) << m[1][0] <<
          " " << std::setw (width) << m[1][1] <<
          " " << std::setw (width) << m[1][2] <<
          " " << std::setw (width) << m[1][3] << "\n" <<

          " " << std::setw (width) << m[2][0] <<
          " " << std::setw (width) << m[2][1] <<
          " " << std::setw (width) << m[2][2] <<
          " " << std::setw (width) << m[2][3] << "\n" <<

          " " << std::setw (width) << m[3][0] <<
          " " << std::setw (width) << m[3][1] <<
          " " << std::setw (width) << m[3][2] <<
          " " << std::setw (width) << m[3][3] << ")\n";

        s.flags (oldFlags);
        return s;
    }
};

//ToDo: Documentation
template<typename T>
void Matrix44<T>::multVecMatrix(const Vec3<T> &src, Vec3<T> &dst) const {
    T a, b, c, w;
    a = src.x * m[0][0] + src.y * m[1][0] + src.z * m[2][0] + m[3][0];
    b = src.x * m[0][1] + src.y * m[1][1] + src.z * m[2][1] + m[3][1];
    c = src.x * m[0][2] + src.y * m[1][2] + src.z * m[2][2] + m[3][2];
    w = src.x * m[0][3] + src.y * m[1][3] + src.z * m[2][3] + m[3][3];
    if (w != 0) {
        dst.x = a / w;
        dst.y = b / w;
        dst.z = c / w;
    }
}

//ToDo: Documentation
template<typename T>
void Matrix44<T>::multDirMatrix(const Vec3<T> &src, Vec3<T> &dst) const {
    dst.x = src.x * m[0][0] + src.y * m[1][0] + src.z * m[2][0];
    dst.y = src.x * m[0][1] + src.y * m[1][1] + src.z * m[2][1];
    dst.z = src.x * m[0][2] + src.y * m[1][2] + src.z * m[2][2];
}

typedef Matrix44<float> Matrix44f;

#endif //SCRATCHPIXEL_MATRIX_H

