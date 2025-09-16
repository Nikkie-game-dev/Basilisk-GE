#include "Shape.h"

namespace basilisk
{
    Shape::Shape(const bool isSolidColor, const basilisk::Color color) :
        Entity2D(isSolidColor), Color(color)
    {
    }
}
