#pragma once

#include "Export.h"
#include "Shape2D.h"

namespace basilisk
{
    /// <summary>
    /// Primitive square shape. The color can be provided by the Color class or read from material.
    /// </summary>
    class BASILISK_API Square : public Shape2D
    {
    protected:
        Square(const vec2& center, const vec2& size, bool isSolidColor, basilisk::Color color);

    private:

        /// <summary>
        /// Initializes the vertices that will be used for drawing the square.
        /// </summary>
        void SetVertices() override;
        void SetIndices() override;

    };
} // basilisk 
