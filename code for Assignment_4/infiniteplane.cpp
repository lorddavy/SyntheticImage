#include "infiniteplane.h"

InfinitePlane::InfinitePlane(const Vector3D &p0_, const Vector3D &normal_,
         Material *mat_) :
    Shape(Matrix4x4(), mat_),
    p0World(p0_), nWorld(normal_.normalized())
{ }

Vector3D InfinitePlane::getNormalWorld() const
{
    return nWorld;
}

bool InfinitePlane::rayIntersectP(const Ray &rayWorld) const
{
    // Compute the denominator of the tHit formula
    // (..)

    // If the denominator is very close to zero, then the ray and the
    // plane are almost parallel
    if(std::abs(denominator) < Epsilon)
        return false;

    // Effectivelly compute the intersection point
    //(...)

    // Is tHit outside the bounds of the ray segment we want to test intersecion with?
    if (tHit < rayWorld.minT || tHit > rayWorld.maxT)
        return false;

    // Arriving here, we know that the ray segment intersects the plan
    return true;
}

bool InfinitePlane::rayIntersect(const Ray &rayWorld, Intersection &its) const
{
    // Compute the denominator of the tHit formula
    // (..)

    // Test for parallel ray/plane
    // (..)

    // Effectivelly compute the intersection distance
    //(...)

    // Is tHit outside the bounds of the ray segment we want to test intersecion with?
    // (..)

    // Compute ray/plane the intersection point
    // (..)

    // Fill the intersection details
    //(...)

    // Update the ray maxT
    // (...)

    return true;
}




std::string InfinitePlane::toString() const
{
    std::stringstream s;
    s << "\tInfinitePlan attributes: \n";

    s << "\t p0 (world coordinates): " << p0World << "\n";
    s << "\t normal (world coordinates): " << nWorld << "\n" << std::endl;

    return s.str();
}

std::ostream &operator<<(std::ostream &out, const InfinitePlane &t)
{
    out << t.toString();
    return out;
}
