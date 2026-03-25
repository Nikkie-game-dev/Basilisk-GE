#pragma once

#include "Entity2D.h"

namespace basilisk
{
    /// <summary>
    /// Abstract class for primitive shapes.
    /// </summary>
    class BASILISK_API Shape : public Entity2D
    {
    public:
        virtual ~Shape() = default;

    protected:
        explicit Shape(const utils::Color& color, bool isSolid);
        
        /// <summary>
        /// Initializes the vertices that will be used for drawing.
        /// </summary>
        virtual void SetVertices() = 0;
        bool IsSolid;
    };
} // basilisk 
