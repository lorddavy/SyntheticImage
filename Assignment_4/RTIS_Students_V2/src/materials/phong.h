#ifndef PHONG_H
#define PHONG_H

#include "../core/vector3d.h"
#include "material.h"

class Phong : public Material
{
public:
	Vector3D kd, ks;
	float s;

    Phong(Vector3D kd, Vector3D ks, float s);

    virtual Vector3D getReflectance(const Vector3D &n, const Vector3D &wo,
                                    const Vector3D &wi) const;
    bool hasSpecular() const;
    bool hasTransmission() const;
    bool hasDiffuseOrGlossy() const;
    //double getIndexOfRefraction() const;
};


#endif // PHONG
