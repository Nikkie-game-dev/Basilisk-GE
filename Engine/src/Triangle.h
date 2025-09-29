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
        /// <summary>
        /// Calculates the vertices of the triangle. Overrides the function that comes from shape.
        /// </summary>
        /// <param name="center">The center of the shape</param>
        /// <param name="size">The size (x = width and y = height) of the shape</param>
        void CalculateVertices(glm::vec2 center, glm::vec2 size) override;
        /// <summary>
        /// Initializes the vertices that will be used for drawing the triangle.
        /// </summary>
        void SetVertices() override;

        glm::vec2 Top;
        glm::vec2 BottomLeft;
        glm::vec2 BottomRight;

    };
} // basilisk 
