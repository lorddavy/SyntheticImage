#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "camera.h"

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera() = delete;

    PerspectiveCamera(const Matrix4x4 &cameraToWorld_, const double fov,
                const Film &film_ );

    // Member functions
    virtual Ray generateRay(const double u, const double v) const;
    virtual Vector3D ndcToCameraSpace(const double u, const double v) const;

    /* Perspective Camera Data */
    double fov; // Radians
};

#endif // PERSPECTIVE_H
