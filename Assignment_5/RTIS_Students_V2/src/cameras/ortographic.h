#ifndef ORTOGRAPHICCAMERA_H
#define ORTOGRAPHICCAMERA_H

#include "camera.h"


// Ortographic Camera Interface
class OrtographicCamera : public Camera
{
public:

    OrtographicCamera() = delete;

    OrtographicCamera(const Matrix4x4 &cameraToWorld_,
                      const Film &film_ );

    // Member functions
    virtual Ray generateRay(const double u, const double v) const;
    virtual Vector3D ndcToCameraSpace(const double u, const double v) const;
};

#endif // ORTOGRAPHICCAMERA_H
