#include "Shape3D.h"

namespace basilisk
{

    Shape3D::Shape3D(bool isSolid, const vec3& center, const vec3& size, const basilisk::Color& color) :
        Shape(isSolid), Color(color)
    {
        this->SetPosition(center);
        this->SetScaling(size);
    }
}
