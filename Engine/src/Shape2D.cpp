#include "Shape2D.h"

namespace basilisk
{
    Shape2D::Shape2D(bool isSolid,
                     const vec2& center,
                     const vec2& size,
                     const basilisk::Color color) :
        Shape(isSolid)
    {
        this->Entity2D::SetPosition(center);
        this->Entity2D::SetScaling(size);
        this->Color = color;
    }
}
