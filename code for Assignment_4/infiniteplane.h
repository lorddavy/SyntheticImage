#ifndef INFINITEPLANE_H
#define INFINITEPLANE_H

#include "shape.h"

class InfinitePlane : public Shape
{
public:
    InfinitePlane() = delete;
    InfinitePlane(const Vector3D &p0_, const Vector3D &normal_,
                 Material *mat_);

    // Get the normal at a surface point in world coordinates
    Vector3D getNormalWorld() const;

    // Ray/plane intersection methods
    virtual bool rayIntersect(const Ray &ray, Intersection &its) const;
    virtual bool rayIntersectP(const Ray &ray) const;

    // Convert triangle to String
    std::string toString() const;

private:
    // A point belonging to the plane, and the normal at the plane
    /* All values are in world coordinates */
    Vector3D p0World;
    Vector3D nWorld;
};

std::ostream &operator<<(std::ostream &out, const InfinitePlane &t);

#endif // INFINITEPLANE_H
