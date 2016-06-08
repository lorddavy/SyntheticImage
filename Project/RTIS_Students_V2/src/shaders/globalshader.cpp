#include "globalshader.h"
#include "directshader.h"
#include "../core/utils.h"
#include "../core/hemisphericalsampler.h"

GlobalShader::GlobalShader()
{}

GlobalShader::GlobalShader(Vector3D color_, double maxDist_, Vector3D bgColor_) :
	color(color_), Shader(bgColor_), maxDist(maxDist_)
{
	directShader = new DirectShader(color, maxDist, bgColor);
}


Vector3D GlobalShader::computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList) const
{
	//Vector3D iDir;
	//DirectShader directShader = DirectShader(color, maxDist, bgColor);
	//Vector3D iDir = directShader->computeColor(r, objList, lsList);

	//DirectShader
	Intersection closestInt;
	Vector3D color = Vector3D(0, 0, 0);

	if (Utils::getClosestIntersection(r, objList, closestInt))
	{
		Vector3D p = closestInt.itsPoint;
		Vector3D n = closestInt.normal;

		Vector3D iDir;
		Vector3D iInd;

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

			float at = 0.1; //Se tendra que pasar como parametro
			Vector3D kd = closestInt.shape->getMaterial().getDiffuseCoefficient();
			//Vector3D iInd;

			
			if (r.depth == 0)
			{
				int nSamples = 500;
				Vector3D sumatory = Vector3D(0);
				HemisphericalSampler sampler;

				for (int i = 0; i < nSamples; i++) {
					Vector3D wi_dir = sampler.getSample(n);
					Ray wi = Ray(p, wi_dir, r.depth + 1);

					Vector3D reflectance = closestInt.shape->getMaterial().getReflectance(n, -r.d, wi_dir);
					sumatory += Utils::multiplyPerCanal(computeColor(wi, objList, lsList), reflectance);
					//sumatory += computeColor(wi, objList, lsList);
				}

				iInd = sumatory / nSamples;
			}else if (r.depth > 0) {
				iInd = kd * at;
			}
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
					Ray refractionRay(closestInt.itsPoint, wt, r.depth);
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
			Ray reflectionRay(closestInt.itsPoint, wr, r.depth);
			Vector3D reflectance = closestInt.shape->getMaterial().getReflectance(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
			color += Utils::multiplyPerCanal(computeColor(reflectionRay, objList, lsList), reflectance);

		}
		return color;
	}
	else
		return bgColor;
}
