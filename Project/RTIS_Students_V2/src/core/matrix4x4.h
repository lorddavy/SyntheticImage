#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <sstream>

#include "vector3d.h"
#include "ray.h"

using std::ostream;
using std::string;

// Matrix stored in row-major form
struct Matrix4x4
{
    // Constructors
    Matrix4x4();
    Matrix4x4(double data_[4][4]);
    Matrix4x4( double a00, double a01, double a02, double a03,
               double a10, double a11, double a12, double a13,
               double a20, double a21, double a22, double a23,
               double a30, double a31, double a32, double a33);

    //Matrix4x4(Matrix4x4);

    // Member operators overload
    Matrix4x4 operator+(const Matrix4x4 &m) const;
    Matrix4x4 operator-(const Matrix4x4 &m) const;
    Matrix4x4 operator*(const Matrix4x4 &m) const;
    Matrix4x4 operator*(const double     a) const;
    /*Matrix4x4& operator+=(const Matrix4x4 &m);
    Matrix4x4& operator-=(const Matrix4x4 &m);
    Matrix4x4& operator*=(const Matrix4x4 &m);*/

    // Member functions (Transformations)
    Vector3D transformVector(const Vector3D &v) const;
    Vector3D transformPoint(const Vector3D &p) const;
    Ray      transformRay(const Ray &r) const;

    //Vector3D  multiplyNormal(const Vector3D  &n) const;
    std::string toString() const;
    bool inverse(Matrix4x4 &target) const;
    void setToZeros();
    void transpose(Matrix4x4 &target) const;
    // determinant ?

    // Static methods
    static Matrix4x4 translate(const Vector3D &delta);
    static Matrix4x4 scale(const Vector3D &scalingVector);
    static Matrix4x4 rotate(const double angleInRad, const Vector3D &axis);


    // Structure data
    double data[4][4];
};

// Stream insertion operator
ostream& operator<<(ostream &out, const Matrix4x4& m);

#endif // MATRIX_H
