#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vector3d.h"

class Shape;

// Class used to store information regarding the
// intersection point.
// Based on PBRT (Chapter 2)
class Intersection
{
public:
    Intersection();

    //  Position of the 3D point (i.e., the intersection point in world coordinates)
    Vector3D itsPoint;

    // The surface normal at the intersection point (also in world coordinates)
    Vector3D normal;

    // Pointer to the shape that the intersection point lies on
    const Shape *shape;
};

#endif // INTERSECTION_H
