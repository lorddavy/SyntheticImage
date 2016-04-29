#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <string>

#include "shape.h"
#include "../core/eqsolver.h"

class Sphere : public Shape
{
public:
    Sphere() = delete;
    Sphere(const double radius_, const Matrix4x4 &t);

    virtual bool rayIntersectP(const Ray &ray) const;
    std::string toString() const;

private:
    // The center of the sphere in local coordinates is assumed
    // to be (0, 0, 0). To pass to world coordinates just apply the
    // objectToWorld transformation contained in the mother class
    double radius;
};

std::ostream& operator<<(std::ostream &out, const Sphere &s);

#endif // SPHERE_H
