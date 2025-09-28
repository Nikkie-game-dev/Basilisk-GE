#pragma once

#include "Shape.h"
#include "Export.h"

namespace basilisk
{
    class BASILISK_API Square : public Shape
    {
    public:
        Square(glm::vec2 topLeftPos, glm::vec2 size, bool isSolidColor, basilisk::Color color);
        void Init() override;
        void Draw();

    private:
        void SetVerticesSolid(glm::vec2 topLeftPos, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight);
        void SetVertices(glm::vec2 topLeftPos, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight);
    };
} // basilisk 
