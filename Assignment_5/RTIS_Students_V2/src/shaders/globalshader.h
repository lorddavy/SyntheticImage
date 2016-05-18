#ifndef GLOBALSHADER_H
#define GLOBALSHADER_H

#include "shader.h"

class GlobalShader : public Shader
{
public:
	GlobalShader();
	GlobalShader(Vector3D color_, double maxDist_, Vector3D bgColor_);

	virtual Vector3D computeColor(const Ray &r,
		const std::vector<Shape*> &objList,
		const std::vector<PointLightSource> &lsList) const;

private:
	Vector3D color; // Used to store the visualization color
};

#endif // GLOBALSHADER_H
