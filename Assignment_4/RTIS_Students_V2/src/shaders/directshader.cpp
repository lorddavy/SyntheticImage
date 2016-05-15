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
	Vector3D color = Vector3D(0, 0, 0);

	if (Utils::getClosestIntersection(r, objList, closestInt))
	{
		Vector3D p = closestInt.itsPoint;
		Vector3D n = closestInt.normal;

		if(closestInt.shape->getMaterial().hasDiffuseOrGlossy())
		{
			for (int i = 0; i < lsList.size(); i++)
			{
				Vector3D wi = (lsList[i].getPosition() - closestInt.itsPoint);
				double maxT = wi.length();
				wi = wi.normalized();

				Ray shadowRay(closestInt.itsPoint, wi);
				shadowRay.maxT = maxT;
				if (dot(wi, n) > 0)
				{
					if (!Utils::hasIntersection(shadowRay, objList))
					{
						Vector3D reflectance = closestInt.shape->getMaterial().getReflectance(n, -r.d, wi);
						color += Utils::multiplyPerCanal(lsList[i].getIntensity(p), reflectance);
					}
				}
			}
		}
		if (closestInt.shape->getMaterial().hasSpecular())
		{			
			Vector3D wr = Utils::computeReflectionDirection(r.d, n);
			Ray reflectionRay(closestInt.itsPoint, wr, r.depth+1);
			Vector3D reflectance = closestInt.shape->getMaterial().getReflectance(Vector3D(0,0,0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
			color += Utils::multiplyPerCanal(computeColor(reflectionRay, objList, lsList),reflectance);

		}
		if (closestInt.shape->getMaterial().hasTransmission())
		{
			double eta = closestInt.shape->getMaterial().getIndexOfRefraction();
			double cosThetaI = dot(n, -r.d);
			double cosThetaT_out = 0.5;
			
			//For debug
			//Ray refractionRay(closestInt.itsPoint, r.d, r.depth + 1);

			if (!Utils::isTotalInternalReflection(eta, cosThetaI, cosThetaT_out))
			{	
				cosThetaT_out = sqrt(1 + eta*eta*(cosThetaI*cosThetaI - 1));

				if (cosThetaI < 0)
				{
					cosThetaI *= -1;
					n = -n;
				}


				Vector3D wt = Utils::computeTransmissionDirection(r, n, eta, cosThetaI, cosThetaT_out);
				Ray refractionRay(closestInt.itsPoint, wt, r.depth + 1);
				Vector3D reflectance = closestInt.shape->getMaterial().getReflectance(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
				color += Utils::multiplyPerCanal(computeColor(refractionRay, objList, lsList), reflectance);
			}
			else
			{
				Vector3D wr = Utils::computeReflectionDirection(r.d, n);
				Ray reflectionRay(closestInt.itsPoint, wr, r.depth + 1);
				Vector3D reflectance = closestInt.shape->getMaterial().getReflectance(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
				color += Utils::multiplyPerCanal(computeColor(reflectionRay, objList, lsList), reflectance);
			}
		}
		return color;
	}
	else
		return bgColor;
}
