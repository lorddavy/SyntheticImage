#include "ortographic.h"

OrtographicCamera::OrtographicCamera(const Matrix4x4 &cameraToWorld_,
                  const Film &film_ )
    : Camera(cameraToWorld_, film_)
{ }


Vector3D OrtographicCamera::ndcToCameraSpace(const double u, const double v) const
{
    // Compute the x-coordinate in camera space (taking into account the aspect ratio)
    double x = ((u * 2) - 1) * aspect;
    // Compute the x-coordinate in camera space
    double y = ((v * 2) - 1);

    // Return the position in camera space
    return Vector3D(x, y, 0);
}


// Input in image space
Ray OrtographicCamera::generateRay(const double u, const double v) const
{
    // Convert the from ndc to camera coordinates
    Vector3D rOrig = ndcToCameraSpace(u, v);

    // COMPLETE THE REST OF THE FUNCTION

    // Make sure the ray is normalized!

    return Ray();
}
