#include "ortographic.h"

OrtographicCamera::OrtographicCamera(const Matrix4x4 &cameraToWorld_,
                  //const double nearClip_, const double farClip_,
                  const Film &film_ )
    //: Camera(cameraToWorld_, nearClip_, farClip_, film_)
    : Camera(cameraToWorld_, film_)
{
    // Build the necessary transforms
//    Vector3D delta(-1.0, -1.0, 0);

//    ndcToCamera =  Matrix4x4::scale(Vector3D(aspect, 1.0, 1.0)) *
//                   Matrix4x4::translate(delta) *
//                   Matrix4x4::scale(Vector3D(2.0, 2.0, 1.0)) *
//                   Matrix4x4::scale(Vector3D(1.0, 1.0, farClip - nearClip));
}

Vector3D OrtographicCamera::ndcToCameraSpace(const double u, const double v) const
{
    // Compute the x-coordinate in camera space (taking into account the aspect ratio)
    double x = ((u * 2) - 1) * aspect;
    // Compute the x-coordinate in camera space
    double y = ((v * 2) - 1);

    // Return the position in camera space
    return Vector3D(x, y, 0);
}

// Input in Image plane
Ray OrtographicCamera::generateRay(const double u, const double v) const
{
    // Convert the sample to camera coordinates
    //Vector3D rOrig = ndcToCamera.transformPoint(sample);
    Vector3D rOrig = ndcToCameraSpace(u, v);

    Vector3D rDir(0, 0, 1);

    // Construct the ray
    size_t rayDepth = 0;
    Ray r(rOrig, rDir, rayDepth);

    // Convert the ray to world coordinates
    r = cameraToWorld.transformRay(r);

    // Make sure the ray is normalized
    r.d = r.d.normalized();

    return r;
}
