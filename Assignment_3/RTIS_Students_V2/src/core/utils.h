#ifndef UTILS_H
#define UTILS_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>

#include "ray.h"
#include "../shapes/shape.h"


class Utils
{
public:
    Utils();

    static bool getClosestIntersection(const Ray &cameraRay, const std::vector<Shape*> &objectsList, Intersection &its);
    static bool hasIntersection(const Ray &ray, const std::vector<Shape*> &objectsList);
    static Vector3D scalarToRGB(double scalar);
    static double degreesToRadians(double degrees);

    static Vector3D multiplyPerCanal(const Vector3D &v1, const Vector3D &v2);
//    static Vector3D sumPerCanal(const Vector3D &v1, const Vector3D &v2);

    static Vector3D computeReflectionDirection(const Vector3D &rayDirection, const Vector3D &normal);

    static bool isTotalInternalReflection(const double &eta, const double &cosThetaI,
                                          double &cosThetaT_out);

    static Vector3D computeTransmissionDirection(const Ray &r, const Vector3D &normal,
                                                 const double &eta, const double &cosThetaI,
                                                 const double &cosThetaT);

    static double computeReflectanceCoefficient(const double &eta, const double &cosThetaI,
                                                const double &cosThetaT);
};

#endif // UTILS_H
