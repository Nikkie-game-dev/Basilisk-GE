#include "Shape.h"

#include "Colors.h"

namespace basilisk
{
    Shape::Shape(const utils::Color& color, const bool isSolid) :
        IsSolid(isSolid)
    {
        this->Color = color;
    }
}
