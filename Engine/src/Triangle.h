// 28/09/2025 - Basilisk-GE

#pragma once
#include "Shape.h"

namespace basilisk
{
    /// <summary>
    /// Primitive triangle shape. The color can be provided by the Color class or read from material.
    /// </summary>
    class BASILISK_API Triangle : public Shape
    {
    protected:
        explicit Triangle(glm::vec2 center, glm::vec2 size, bool isSolid, const basilisk::Color& color);

    private:
        void SetVertices() override;
    };
} // basilisk 
