#pragma once

#include "Colors.h"
#include "Entity2D.h"
#include "Export.h"

namespace basilisk
{

    class BASILISK_API Shape : public Entity2D
    {
    public:
        explicit Shape(Color color);
        virtual ~Shape() = default;

    protected:
        Color Color;
    };
} // basilisk 
