#ifndef SHAPE_H
#define SHAPE_H

#include "../core/matrix4x4.h"
#include "../core/vector3d.h"
#include "../core/ray.h"

class Intersection;

class Shape
{
public:
    Shape() = delete;
    Shape(const Matrix4x4 &t_);

    // Pure virtual function makes this class Abstract class.
    // Ray-shape intersection methods
    virtual bool rayIntersectP(const Ray &ray) const = 0;

protected:
    Matrix4x4 objectToWorld;
    Matrix4x4 worldToObject;
};

#endif // SHAPE_H
