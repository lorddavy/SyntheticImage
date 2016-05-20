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
		if (kd.x != -1)
		{
			//Vector3D iInd = kd * at;
			if (r.depth == 0)
			{
				int nSamples;
				Vector3D result = Vector3D(0);

				for (int i = 0; i < nSamples; i++) {
					Vector3D formula; //calculate formula
					result += formula;
				}		
				
				Vector3D iInd = 
			}

			color = iDir + iInd;
		}
		else {
			color = iDir;
		}
		
		return color;
	}

	return iDir;
}
