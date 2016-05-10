#ifndef MIRROR_H
#define MIRROR_H

#include "../core/vector3d.h"
#include "material.h"

class Mirror : public Material
{
public:
	//Vector3D;

	Mirror();

    virtual Vector3D getReflectance(const Vector3D &n, const Vector3D &wo,
                                    const Vector3D &wi) const;
    bool hasSpecular() const;
    bool hasTransmission() const;
    bool hasDiffuseOrGlossy() const;
    //double getIndexOfRefraction() const;
};


#endif // MIRROR
