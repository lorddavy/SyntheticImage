#include "utils.h"

Utils::Utils()
{ }

double Utils::degreesToRadians(double degrees)
{
    return degrees * M_PI / 180.0;
}

Vector3D Utils::multiplyPerCanal(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
}

bool Utils::hasIntersection(const Ray &ray, const std::vector<Shape*> &objectsList)
{
    std::cout << "Need to implement the function Utils::hasIntersection() in the file utils.cpp" << std::endl;

    // Write your code bellow
    // (...)
    //
    // For each object on the scene...
    //for(size_t objIndex = 0; objIndex < objectsList.size(); objIndex ++)
    //{
    //      // Get the current object
    //      const Shape *obj = objectsList.at(objIndex);
    //      (...)
    //}
    //
    // (...)
    //

    return false;
}

bool Utils::getClosestIntersection(const Ray &cameraRay, const std::vector<Shape*> &objectsList, Intersection &its)
{
    std::cout << "Need to implement the function Utils::getClosestIntersection() in the file utils.cpp" << std::endl;

    //
    // Write your code bellow
    //
    // (...)
    //

    return false;
}

double interpolate(double val, double y0, double x0, double y1, double x1 )
{
    return (val-x0)*(y1-y0)/(x1-x0) + y0;
}

double getRed(double value)
{
    if (value > 0.5)
        return interpolate( value, 0.0, 0.5, 1.0, 1.0 );
    else
        return 0.0;
}

double getGreen(double value)
{
    if (value < 0.25)
        return 0.0;
    else if (value < 0.5)
        return interpolate(value, 0.0, 0.25, 1, 0.5);
    else if (value < 0.75)
        return interpolate(value, 1, 0.5, 0, 0.75);
    else
        return 0;
}

double getBlue(double value)
{
    if (value < 0.5)
        return interpolate(value, 1.0, 0.0, 0.0, 0.5);
    else
        return 0;
}


Vector3D Utils::scalarToRGB(double scalar)
{
    return Vector3D( getRed(scalar),
                getGreen(scalar),
                getBlue(scalar) );
}

Vector3D Utils::computeReflectionDirection(const Vector3D &rayDirection, const Vector3D &normal)
{
    // Compute the perfect reflection direction
    return normal * 2 * dot(normal, -rayDirection) + rayDirection;
}

bool Utils::isTotalInternalReflection(const double &eta, const double &cosThetaI,
                                      double &cosThetaT_out)
{
    return false;
}

Vector3D Utils::computeTransmissionDirection(const Ray &r, const Vector3D &normal,
                                             const double &eta, const double &cosThetaI,
                                             const double &cosThetaT)
{
    return Vector3D(0);
}

double Utils::computeReflectanceCoefficient(const double &eta, const double &cosThetaI,
                                            const double &cosThetaT)
{
    return 0.0;
}
