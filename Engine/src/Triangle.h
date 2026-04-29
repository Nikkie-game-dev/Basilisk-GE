// 28/09/2025 - Basilisk-GE

#pragma once
#include "Shape2D.h"

namespace basilisk
{
    /// <summary>
    /// Primitive triangle shape. The color can be provided by the Color class or read from material.
    /// </summary>
    class BASILISK_API Triangle : public Shape2D
    {
    protected:
        explicit Triangle(const vec2& center, const vec2& size, bool isSolid, const basilisk::Color& color);

    private:
        void SetVertices() override;
        void SetIndices() override;
    };
} // basilisk 
