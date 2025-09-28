// 28/09/2025 - Basilisk-GE

#pragma once
#include "Shape.h"

namespace basilisk
{
    class BASILISK_API Triangle : public Shape
    {
    protected:
        explicit Triangle(glm::vec2 center, glm::vec2 size, bool isSolid, const basilisk::Color& color);

    private:
        void CalculateVertices(glm::vec2 center, glm::vec2 size) override;
        void SetVertices() override;

        glm::vec2 Top;
        glm::vec2 BottomLeft;
        glm::vec2 BottomRight;

    };
} // basilisk 
