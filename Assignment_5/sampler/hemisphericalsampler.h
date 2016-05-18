#ifndef HEMISPHERICALSAMPLER_H
#define HEMISPHERICALSAMPLER_H

#include "../core/vector3d.h"

class HemisphericalSampler
{
public:
    HemisphericalSampler();
    Vector3D getSample(const Vector3D &normal) const;
};

#endif // HEMISPHERICALSAMPLER_H
