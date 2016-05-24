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
	Vector3D iDir;
	//DirectShader directShader = DirectShader(color, maxDist, bgColor);
	//Vector3D iDir = directShader->computeColor(r, objList, lsList);

	//DirectShader
	Intersection closestInt;
	Vector3D color = Vector3D(0, 0, 0);

	if (Utils::getClosestIntersection(r, objList, closestInt))
	{
		Vector3D p = closestInt.itsPoint;
		Vector3D n = closestInt.normal;

		bool diffuse = closestInt.shape->getMaterial().hasDiffuseOrGlossy();
		bool specular = closestInt.shape->getMaterial().hasSpecular();
		bool transmission = closestInt.shape->getMaterial().hasTransmission();

		if (diffuse)
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
						iDir += Utils::multiplyPerCanal(lsList[i].getIntensity(p), reflectance);
					}
				}
			}

			float at = 0.1;
			Vector3D kd = closestInt.shape->getMaterial().getDiffuseCoefficient();
			Vector3D iInd = kd * at;

			/*
			if (r.depth == 0)
			{
				int nSamples = 10;
				Vector3D result = Vector3D(0);

				for (int i = 0; i < nSamples; i++) {
					Vector3D formula; //calculate formula
					result += formula;
				}

				iInd = Vector3D(1, 0, 0);
			}*/

			color = iDir + iInd;
		}
		if (transmission)
		{

			double eta = closestInt.shape->getMaterial().getIndexOfRefraction();
			double cosThetaI = dot(-r.d, n);
			double cosThetaT_out;

			if (cosThetaI < 0)
			{
				n *= -1;
				eta = 1 / closestInt.shape->getMaterial().getIndexOfRefraction();
				cosThetaI = dot(-r.d, n);
			}

			if (!Utils::isTotalInternalReflection(eta, cosThetaI, cosThetaT_out))
			{
				cosThetaT_out = sqrt(1 + eta*eta*(cosThetaI*cosThetaI - 1));

				Vector3D wt = Utils::computeTransmissionDirection(r, n, eta, cosThetaI, cosThetaT_out);

				if (r.depth < maxDist)
				{
					Ray refractionRay(closestInt.itsPoint, wt, r.depth + 1);
					color = computeColor(refractionRay, objList, lsList);
				}
			}
			else
			{
				specular = true;
			}
		}
		if (specular)
		{
			Vector3D wr = Utils::computeReflectionDirection(r.d, n);
			Ray reflectionRay(closestInt.itsPoint, wr, r.depth + 1);
			Vector3D reflectance = closestInt.shape->getMaterial().getReflectance(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
			color += Utils::multiplyPerCanal(computeColor(reflectionRay, objList, lsList), reflectance);

		}
		return color;
	}
	else
		return bgColor;
}
