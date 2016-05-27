#ifndef GLOBALSHADER_H
#define GLOBALSHADER_H

#include "shader.h"

class DirectShader;

class GlobalShader : public Shader
{
public:
	GlobalShader();
	GlobalShader(Vector3D color_, double maxDist_, Vector3D bgColor_);

	DirectShader *directShader;

	virtual Vector3D computeColor(const Ray &r,
		const std::vector<Shape*> &objList,
		const std::vector<PointLightSource> &lsList) const;

private:
	Vector3D color; // Used to store the visualization color
	double maxDist;
};

#endif // GLOBALSHADER_H
