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
        /// <summary>
        /// Calculates the vertices of the square. Overrides the function that comes from shape.
        /// </summary>
        /// <param name="center">The center of the shape</param>
        /// <param name="size">The size (x = width and y = height) of the shape</param>
        void CalculateVertices(glm::vec2 center, glm::vec2 size) override;
        /// <summary>
        /// Initializes the vertices that will be used for drawing the square.
        /// </summary>
        void SetVertices() override;

        glm::vec2 TopLeft;
        glm::vec2 TopRight;
        glm::vec2 BottomLeft;
        glm::vec2 BottomRight;

    };
} // basilisk 
