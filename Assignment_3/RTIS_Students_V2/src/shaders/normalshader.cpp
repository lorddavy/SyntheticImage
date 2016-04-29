#include "normalshader.h"
#include "../core/utils.h"

NormalShader::NormalShader()
{}

NormalShader::NormalShader(Vector3D bgColor_) :
    Shader(bgColor_)
{}

Vector3D NormalShader::computeColor(const Ray &r, const std::vector<Shape *> &objList, const std::vector<PointLightSource> &lsList) const
{
    Intersection its;

    if (Utils::getClosestIntersection(r, objList, its))
    {
        Vector3D res = (its.normal + Vector3D(1.0)) / 2.0;
        return res;
    } else
    {
        return bgColor;
    }
}
