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
        /// Initializes the vertices that will be used for drawing the square.
        /// </summary>
        void SetVertices() override;

    };
} // basilisk 
