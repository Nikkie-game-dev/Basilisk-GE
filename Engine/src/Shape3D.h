// 29/04/2026 - Basilisk-GE

#pragma once
#include "Colors.h"
#include "Entity.h"
#include "Shape.h"

namespace basilisk
{
    class Shape3D : public Shape, public Entity
    {
    protected:
        Shape3D(bool isSolid,
                const vec3& center,
                const vec3& size,
                const Color& color = basilisk::Color(0, 0, 0));
        Color Color;

    };
} // basislisk 
