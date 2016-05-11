#include "mirror.h"
#include <algorithm>

// Implement the Constructors here
Mirror::Mirror(Vector3D color_)
: color(color_)
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
	return color;
}