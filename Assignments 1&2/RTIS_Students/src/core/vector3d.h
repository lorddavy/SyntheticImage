#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <ostream>

struct Vector3D
{
    // Constructors
    Vector3D();
    Vector3D(double a);
    Vector3D(double x_, double y_, double z_);
    Vector3D(const Vector3D &v_);

    // Member operators overload
    Vector3D operator+(const Vector3D &v) const;
    Vector3D operator-(const Vector3D &v) const;
    Vector3D operator*(const double a) const;
    Vector3D operator/(const double a) const;
    Vector3D operator-() const;

    Vector3D& operator+=(const Vector3D &v);
    Vector3D& operator-=(const Vector3D &v);
    Vector3D& operator*=(const double a);
    Vector3D& operator/=(const double a);

    // Member functions
    double length()      const;
    double lengthSq()    const;
    Vector3D normalized() const;

    // Structure data
    double x, y, z;
};

// Stream insertion operator (since it takes the user-defined type at the right,
//  i.e., "Vector3D", it must be implemented as non-member
std::ostream& operator<<(std::ostream& out, const Vector3D &v);

// Dot product between two vectors
inline double dot(const Vector3D &v1, const Vector3D &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Returns the cross product between two vectors
inline Vector3D cross(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D( v1.y * v2.z - v1.z * v2.y,
                     v1.z * v2.x - v1.x * v2.z,
                     v1.x * v2.y - v1.y * v2.x );
}

#endif // VECTOR3D_H
