#include "Shape.h"

namespace basilisk
{
    void Shape::Draw()
    {
        Entity2D::Draw(this->Color);
    }
    
    Shape::Shape(const basilisk::Color color, const bool isSolid) :
        Color(color), IsSolid(isSolid)
    {
    }
}
