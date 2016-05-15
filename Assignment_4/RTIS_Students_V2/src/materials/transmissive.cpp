#include "transmissive.h"
#include <algorithm>

// Implement the Constructors here
Transmissive::Transmissive(double a, Vector3D vec) : eta(a), colorVector(vec)
{}


bool Transmissive::hasSpecular() const
{
	return false;
}

bool Transmissive::hasTransmission() const
{
	return true;
}

bool Transmissive::hasDiffuseOrGlossy() const
{
	return false;
}

// Implement the function "getReflectance" here
Vector3D Transmissive::getReflectance(const Vector3D &n, const Vector3D &wo,
	const Vector3D &wi) const 
{
	return colorVector;

}

double Transmissive::getIndexOfRefraction() const
{
	return eta;
}

bool Transmissive::isTotalInternalReflection(double nt, double alpha) const
{
	return 1 + nt * nt * (cos(alpha) * cos(alpha) - 1) < 0;
}