#ifndef INTERSECTIONSHADER_H
#define INTERSECTIONSHADER_H

#include "shader.h"

class IntersectionShader : public Shader
{
public:
    IntersectionShader();
    IntersectionShader(Vector3D hitColor, Vector3D bgColor_);

    virtual Vector3D computeColor(const Ray &r,
                             const std::vector<Shape*> &objList,
                             const std::vector<PointLightSource> &lsList) const;

    Vector3D hitColor;
};

#endif // INTERSECTIONSHADER_H
