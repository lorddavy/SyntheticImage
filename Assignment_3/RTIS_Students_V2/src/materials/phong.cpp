#include "phong.h"

// Implement the Constructors here
Phong::Phong(Vector3D kd_, Vector3D ks_, float s_)
	: kd(kd_), ks(ks_), s(s_)
{}


bool Phong::hasSpecular() const
{
	// This material does not have specular component
	return false;
}

bool Phong::hasTransmission() const
{
	return false;
}

bool Phong::hasDiffuseOrGlossy() const
{
	return true;
}

// Implement the function "getReflectance" here
Vector3D Phong::getReflectance(const Vector3D &n, const Vector3D &wo,
	const Vector3D &wi) const 
{
	Vector3D reflectance;
	Vector3D diffuse_color;
	Vector3D specular_color;

	Vector3D wr = n * 2 * dot(n, wi) - wi;

	diffuse_color = kd * dot(wi,n);
	specular_color = ks * pow(dot(wo, wr),s);

	reflectance = diffuse_color + specular_color;
	return reflectance;

}