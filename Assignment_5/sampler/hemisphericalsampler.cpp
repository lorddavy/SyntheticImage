#include "hemisphericalsampler.h"
#include "matrix4x4.h"

#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

HemisphericalSampler::HemisphericalSampler()
{ }

Vector3D HemisphericalSampler::getSample(const Vector3D &normal) const
{
    // Get two i.i.d. random numbers between 0-1
    double psi1 = (double)std::rand() / RAND_MAX;
    double psi2 = (double)std::rand() / RAND_MAX;

    // Generate the direction in spherical coordinates (arround (0, 1, 0))
    double theta = std::acos(psi1);
    double phi   = psi2 * 2 * M_PI;

    // Convert to a 3D vector
    Vector3D randomDir( cos(phi) * sin(theta),
                        psi1,
                        sin(phi) * sin(theta));

    // Construct the local frame (n = yy local)
    Vector3D yL = normal.normalized();
    Vector3D xL = cross(yL, Vector3D(0, 1, 0));
    // Treat the unfortunate case in which xxLocal = 0
    if( std::abs(xL.x) < 0.001 &&
        std::abs(xL.y) < 0.001 &&
        std::abs(xL.z) < 0.001 )
    {
        xL = cross(yL, Vector3D(1, 0, 0));
    }
    Vector3D zL = cross(xL, yL);

    // Compute the rotation matrix between (0, 1, 0) and the provided normal
    Matrix4x4 R(xL.x, yL.x, zL.x, 0,
                xL.y, yL.y, zL.y, 0,
                xL.z, yL.z, zL.z, 0,
                0,    0,    0,    1);

    // Rotate the random direction
    randomDir = R.transformVector(randomDir);

    // Center the hemisphere on the provided normal
    //return rotation.transformVector(randomDir);
    return randomDir;
}