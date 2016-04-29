#include "sphere.h"

Sphere::Sphere(const double radius_, const Matrix4x4 &t_, Material *material_)
    : Shape(t_, material_), radius(radius_)
{ }

// Return the normal in world coordinates
// Pre condition: the point passed as argument to this function is in
// world coordinates and belongs to the sphere
Vector3D Sphere::getNormalWorld(const Vector3D &pt_world) const
{
    // Transform the point to local coordinates
    //Point3D pt_local = worldToObject.applyTransform(pt_world);
    Vector3D pt_local = worldToObject.transformPoint(pt_world);

    // CHECK IF THE POINT EFFECTIVELLY BELONGS TO THE SPHERE?
    // TODO?

    // Normal in local coordinates
    //Normal n(pt_local.x, pt_local.y, pt_local.z);
    Vector3D n(pt_local.x, pt_local.y, pt_local.z);

    // Transform the normal to world coordinates
    //Normal nWorld = objectToWorld.applyTransform(n);
    // Multiply the normal by the transpose of the inverse
    Matrix4x4 inverseTransposed;
    worldToObject.transpose(inverseTransposed);
    Vector3D nWorld = inverseTransposed.transformVector(n);

    // Check whether applying the transform to a normalized
    // normal allways yields a normalized normal
    return(nWorld.normalized());
}

// Chapter 3 PBRT, page 117
bool Sphere::rayIntersect(const Ray &ray, Intersection &its) const
{
    // Pass the ray to local coordinates
    //Ray r = worldToObject.applyTransform(ray);
    Ray r = worldToObject.transformRay(ray);

    // The ray-sphere intersection equation can be expressed in the
    // form A*t^2 + B*t + C = 0, where:
    double A = r.d.x*r.d.x + r.d.y*r.d.y + r.d.z*r.d.z;
    double B = 2*(r.o.x*r.d.x + r.o.y*r.d.y + r.o.z*r.d.z);
    double C = r.o.x*r.o.x + r.o.y*r.o.y +
               r.o.z*r.o.z - radius*radius;

    // Now we need to solve this quadratic equation for t
    EqSolver solver;
    rootValues roots;
    bool hasRoots = solver.rootQuadEq(A, B, C, roots);

    if(!hasRoots)
    {
        return false;
    }

    // Test whether both root values (i.e., the intersection points)
    // are greater or smaller than r.maxT and r.minT, respectivelly
    if (roots.values[0] > r.maxT || roots.values[1] < r.minT)
        return false;

    // If they are not, then there are three possibilities:
    // 1 - t0 > minT and t1 > maxT, in which case t0 is the hit point we want to retain
    // 2 - t0 < minT and t1 < maxT, in which case t1 is the hit point we want to retain
    // 3 - Both roots are out of the ray segment (t0 < minT and t1 > maxT)

    // We initialize the tHit for case 1
    double tHit = roots.values[0];
    // We check where we could possibly be in case 2 or 3
    if (roots.values[0] < ray.minT) {
        // If so, then we set tHit to t1 (hoping we are in case 2!)
        tHit = roots.values[1];
        // If we are in case 3, then return false (meaning there is no intersection detected
        if (tHit > ray.maxT)
            return false;
    }

    // If we arrive here it is because there is an intersection
    // with the tested ray segment!

    // Update the maxT in the ray so as to terminate earlier subsequent
    // intersection tests with other shapes
    ray.maxT = tHit;

    // Compute Intersection Point (in local coordinates)
    Vector3D itsPoint = r.o + r.d*tHit;

    // Transform to world coordinates
    its.itsPoint = objectToWorld.transformPoint(itsPoint);

    // Compute the normal at the intersection point (in world coordinates)
    its.normal   = getNormalWorld(its.itsPoint);

    // Store the shape the intersection point lies in
    its.shape = this;

    return true;
}

// Chapter 3 PBRT, page 117
bool Sphere::rayIntersectP(const Ray &ray) const
{
    // Pass the ray to local coordinates
    Ray r = worldToObject.transformRay(ray);

    // The ray-sphere intersection equation can be expressed in the
    // form A*t^2 + B*t + C = 0, where:
    double A = r.d.x*r.d.x + r.d.y*r.d.y + r.d.z*r.d.z;
    double B = 2*(r.o.x*r.d.x + r.o.y*r.d.y + r.o.z*r.d.z);
    double C = r.o.x*r.o.x + r.o.y*r.o.y +
               r.o.z*r.o.z - radius*radius;

    // Now we need to solve this quadratic equation for t
    EqSolver solver;
    rootValues roots;
    bool hasRoots = solver.rootQuadEq(A, B, C, roots);

    if(!hasRoots)
    {
        return false;
    }

    // Test whether both root values (i.e., the intersection points)
    // are greater or smaller than r.maxT and r.minT, respectivelly
    if (roots.values[0] > r.maxT || roots.values[1] < r.minT)
        return false;

    // If they are not, then there are three possibilities:
    // 1 - t0 > minT and t1 > maxT, in which case t0 is the hit point we want to retain
    // 2 - t0 < minT and t1 < maxT, in which case t1 is the hit point we want to retain
    // 3 - Both roots are out of the ray segment (t0 < minT and t1 > maxT)

    // We initialize the tHit for case 1
    double tHit = roots.values[0];
    // We check where we could possibly be in case 2 or 3
    if (roots.values[0] < ray.minT) {
        // If so, then we set tHit to t1 (hoping we are in case 2!)
        tHit = roots.values[1];
        // If we are in case 3, then return false (meaning there is no intersection detected
        if (tHit > ray.maxT)
            return false;
    }

    // If we arrive here it is because there is an intersection
    // with the tested ray segment!

    // Update the maxT in the ray so as to terminate earlier subsequent
    // intersection tests with other shapes
    ray.maxT = tHit;

    return true;
}

std::string Sphere::toString() const
{
    std::stringstream s;
    s << "[ " << std::endl
      << " Center (World) = " << objectToWorld.transformPoint(Vector3D(0,0,0)) << ", Radius = " << radius << std::endl
      << "]" << std::endl;

    return s.str();
}

std::ostream& operator<<(std::ostream &out, const Sphere &s)
{
    out << s.toString();
    return out;
}
