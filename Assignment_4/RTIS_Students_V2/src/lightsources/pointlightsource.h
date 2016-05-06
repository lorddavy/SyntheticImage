#ifndef POINTLIGHTSOURCE_H
#define POINTLIGHTSOURCE_H

#include "../core/vector3d.h"

// To start, let this be the interface of a point light source
// Then, make this an abstract class from which we can derive:
//   - omnidirectional uniform point light sources
//   - area light sources
class PointLightSource
{
public:
    PointLightSource() = delete;
    PointLightSource(Vector3D pos_, Vector3D intensity_);

    // Getters
    Vector3D getPosition() const;
    Vector3D getIntensity(const Vector3D &dir) const;


private:
    Vector3D pos;
    Vector3D intensity; // (unity: watts/sr)
};

#endif // POINTLIGHTSOURCE_H
