#pragma once
#include "Entity2D.h"
#include "Shape.h"

namespace basilisk
{
    class Shape2D : public Shape, public Entity2D
    {
    public:
         Shape2D(bool isSolid,
                         const vec2& center,
                         const vec2& size,
                         basilisk::Color color = basilisk::Color(0, 0, 0));

    };
} // basilisk 
