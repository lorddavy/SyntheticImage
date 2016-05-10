#include "mirror.h"
#include <algorithm>

// Implement the Constructors here
Mirror::Mirror()
{}


bool Mirror::hasSpecular() const
{
	return true;
}

bool Mirror::hasTransmission() const
{
	return false;
}

bool Mirror::hasDiffuseOrGlossy() const
{
	return false;
}

// Implement the function "getReflectance" here
Vector3D Mirror::getReflectance(const Vector3D &n, const Vector3D &wo,
	const Vector3D &wi) const 
{
	return Vector3D(1);

}