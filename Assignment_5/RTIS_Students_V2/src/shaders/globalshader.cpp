#include "globalshader.h"
#include "directshader.h"
#include "../core/utils.h"

GlobalShader::GlobalShader()
{}

GlobalShader::GlobalShader(Vector3D color_, double maxDist_, Vector3D bgColor_) :
	color(color_), Shader(bgColor_), maxDist(maxDist_)
{
	directShader = new DirectShader(color, maxDist, bgColor);
}


Vector3D GlobalShader::computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList) const
{
	Vector3D color = Vector3D(0, 0, 0);
	//DirectShader directShader = DirectShader(color, maxDist, bgColor);
	Vector3D iDir = directShader->computeColor(r, objList, lsList);

	float at = 0.5;

	Intersection closestInt;

	if (Utils::getClosestIntersection(r, objList, closestInt))
	{
		Vector3D kd = closestInt.shape->getMaterial().getDiffuseCoefficient();
		Vector3D iInd = kd * at;

		color = iDir + iInd;
		return color;
	}

	return bgColor;
}
