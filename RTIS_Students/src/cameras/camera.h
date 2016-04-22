#ifndef CAMERA_H
#define CAMERA_H

#include "../core/film.h"
#include "../core/matrix4x4.h"

class Camera
{
public:
    Camera() = delete;
    Camera(const Matrix4x4 &cameraToWorld_, const Film &film_);

    // Given image plane coordinates (u, v) = [0,1]x[0,1] in normalized
    // device coordinates (NDC), returns a ray in WORLD COORDINATES which passes
    // through (u, v)
    virtual Ray generateRay(const double u, const double v) const = 0;
    virtual Vector3D ndcToCameraSpace(const double u, const double v) const = 0;

    /* ******************* */
    /* General Camera data */
    /* ******************* */

    // The cameraToWorld transformation "places"
    //  the camera in the world
    Matrix4x4 cameraToWorld;
    // Film to store and handle the actual image
    const Film &film;
    // Aspect (based on the film size)
    double aspect;
};

#endif // CAMERA_H
