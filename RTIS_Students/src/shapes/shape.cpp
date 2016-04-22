#include "shape.h"

Shape::Shape(const Matrix4x4 &t_)
{
    objectToWorld = t_;
    objectToWorld.inverse(worldToObject);
}
