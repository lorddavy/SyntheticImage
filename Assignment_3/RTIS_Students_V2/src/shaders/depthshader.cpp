#include "depthshader.h"
#include "../core/utils.h"

DepthShader::DepthShader()
{ 

}

DepthShader::DepthShader(Vector3D color_, double maxDist_, Vector3D bgColor_) :
	color(color_), maxDist(maxDist_), Shader(bgColor_)
{ 

}

Vector3D DepthShader::computeColor(const Ray &r, const std::vector<Shape*> &objList, const std::vector<PointLightSource> &lsList) const
{
	if (Utils::hasIntersection(r, objList))
		//if(r.o-.....)
		
		
		
		return color;



	//OK
	else
		return bgColor;
}
