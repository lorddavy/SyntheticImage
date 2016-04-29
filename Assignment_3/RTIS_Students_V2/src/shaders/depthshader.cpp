#include "depthshader.h"
#include "../core/utils.h"

DepthShader::DepthShader()
{}

DepthShader::DepthShader(Vector3D color_, double maxDist_, Vector3D bgColor_) :
	color(color_), maxDist(maxDist_), Shader(bgColor_)
{}
    
Vector3D DepthShader::computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList) const
{
	Intersection closestInt;
	
	if (Utils::getClosestIntersection(r, objList, closestInt))
	{
		float depth = sqrt((closestInt.itsPoint.x - r.o.x)*(closestInt.itsPoint.x - r.o.x)
			+ (closestInt.itsPoint.y - r.o.y)*(closestInt.itsPoint.y - r.o.y)
			+ (closestInt.itsPoint.z - r.o.z)*(closestInt.itsPoint.z - r.o.z));
		if (depth >= maxDist)
			return bgColor;
		else
			return color * (1.0 - depth/maxDist);
	}
	else
		return bgColor;
	
}
