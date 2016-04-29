#include "pointlightsource.h"

PointLightSource::PointLightSource(Vector3D pos_, Vector3D intensity_) :
    pos(pos_), intensity(intensity_)
{ }

Vector3D PointLightSource::getPosition() const
{
    return pos;
}

Vector3D PointLightSource::getIntensity(const Vector3D &p) const
{
    double sqDistance = (p - pos).lengthSq();

    Vector3D result = intensity / sqDistance;
    return result;
}

