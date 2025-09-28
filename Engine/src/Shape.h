#pragma once

#include "Colors.h"
#include "Entity2D.h"
#include "Export.h"

namespace basilisk
{

    class BASILISK_API Shape : public Entity2D
    {
    public:
        explicit Shape(Color color, bool isSolid);
        virtual ~Shape() = default;

    protected:
        virtual void CalculateVertices(glm::vec2 center, glm::vec2 size) = 0;
        virtual void SetVertices() = 0;
        
        Color Color;
        bool IsSolid;
    };
} // basilisk 
