#pragma once

#include "Shape.h"
#include "Export.h"

namespace basilisk
{
    class BASILISK_API Square : public Shape
    {
    protected:
        Square(glm::vec2 center, glm::vec2 size, bool isSolidColor, basilisk::Color color);

    private:
        void CalculateVertices(glm::vec2 center, glm::vec2 size) override;
        void SetVertices() override;

        glm::vec2 TopLeft;
        glm::vec2 TopRight;
        glm::vec2 BottomLeft;
        glm::vec2 BottomRight;

    };
} // basilisk 
