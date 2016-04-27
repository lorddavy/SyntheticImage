#ifndef SHAPE_H
#define SHAPE_H

#include "../core/matrix4x4.h"
#include "../core/vector3d.h"
#include "../core/ray.h"
#include "../materials/material.h"
#include "../core/intersection.h"

class Shape
{
public:
    Shape() = delete;
    Shape(const Matrix4x4 &t_, Material *material_);

    // Pure virtual function makes this class Abstract class.

    // Ray/shape intersection methods
    virtual bool rayIntersect(const Ray &ray, Intersection &its) const = 0;
    virtual bool rayIntersectP(const Ray &ray) const = 0;

    // Return the material associated with the shape
    const Material& getMaterial() const;

protected:
    Matrix4x4 objectToWorld;
    Matrix4x4 worldToObject;
    Material *material;
};

#endif // SHAPE_H
