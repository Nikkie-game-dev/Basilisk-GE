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
        /// Initializes the vertices that will be used for drawing the triangle.
        /// </summary>
        void SetVertices() override;
    };
} // basilisk 
