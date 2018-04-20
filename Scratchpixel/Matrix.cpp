//
// Created by Thierry Backes on 27/03/18.
//

/*
#include "Matrix.h"


template<typename T>
Matrix44<T> Matrix44<T>::transpose() const {
    Matrix44 transpMat;
    for (uint8_t i = 0; i < 4; ++i) {
        for (uint8_t j = 0; j < 4; ++j) {
            transpMat[i][j] = m[j][i];
        }
    }

    return transpMat;
}
template<typename T>
void Matrix44<T>::multiply(const Matrix44<T> &a, const Matrix44 &b, Matrix44 &c) {
    for (uint8_t i = 0; i < 4; ++i) {
        for (uint8_t j = 0; j < 4; ++j) {
            c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] +
                      a[i][2] * b[2][j] + a[i][3] * b[3][j];
        }
    }
}

template<typename T>
Matrix44<T> Matrix44<T>::transposed() const {
    Matrix44 t;
    for (uint8_t i = 0; i < 4; ++i) {
        for (uint8_t j = 0; j < 4; ++j) {
            t[i][j] = m[j][i];
        }
    }
}

 */