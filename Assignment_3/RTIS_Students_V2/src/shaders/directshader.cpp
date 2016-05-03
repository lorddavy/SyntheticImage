#include "directshader.h"
#include "../core/utils.h"

DirectShader::DirectShader()
{}

DirectShader::DirectShader(Vector3D color_, double maxDist_, Vector3D bgColor_) :
	color(color_), Shader(bgColor_)
{}
    
Vector3D DirectShader::computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList) const
{
	Intersection closestInt;
	Vector3D color = bgColor;
	
	if (Utils::getClosestIntersection(r, objList, closestInt))
	{
		Vector3D p = closestInt.itsPoint;
		Vector3D n = closestInt.normal;
		Vector3D wo = r.o - closestInt.itsPoint;

		for (int i = 0;i < lsList.size();i++)
		{
			Vector3D wi = lsList[i].getPosition() - closestInt.itsPoint;
	
			Ray lightRay(lsList[i].getPosition(),wi);

			if(dot(wi, n)>0)
			{
				if (!Utils::hasIntersection(lightRay, objList))
				{
					Vector3D reflectance = closestInt.shape->getMaterial().getReflectance(n, wo, wi);					
					color += Utils::multiplyPerCanal(lsList[i].getIntensity(p), reflectance);
				}
			}
		}

		return color;
	}
	else
		return color;
	
}
