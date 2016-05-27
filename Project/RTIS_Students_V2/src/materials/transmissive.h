#ifndef TRANSMISSIVE_H
#define TRANSMISSIVE_H

#include "../core/vector3d.h"
#include "material.h"

class Transmissive : public Material
{
private:
	double eta;
	Vector3D colorVector;

public:
	//Vector3D;

	Transmissive(double a, Vector3D vec);

    virtual Vector3D getReflectance(const Vector3D &n, const Vector3D &wo,
                                    const Vector3D &wi) const;
    bool hasSpecular() const;
    bool hasTransmission() const;
    bool hasDiffuseOrGlossy() const;
    double getIndexOfRefraction() const;
	bool isTotalInternalReflection(double nt, double alpha) const;
};


#endif // TRANSMISSIVE
