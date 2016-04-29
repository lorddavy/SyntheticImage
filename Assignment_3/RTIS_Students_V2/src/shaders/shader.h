#ifndef SHADER_H
#define SHADER_H

#include <vector>

#include "../core/ray.h"
#include "../lightsources/pointlightsource.h"
#include "../shapes/shape.h"
#include "../lightsources/pointlightsource.h"

class Shader
{
public:
    Shader();
    Shader(Vector3D bgColor_);

    virtual Vector3D computeColor(const Ray &r,
                             const std::vector<Shape*> &objList,
                             const std::vector<PointLightSource> &lsList) const = 0;

    Vector3D bgColor;
};

#endif // SHADER_H
