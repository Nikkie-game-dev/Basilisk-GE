#pragma once

#include "Macros.h"

namespace basilisk
{
    /// <summary>
    /// Abstract class for primitive shapes.
    /// </summary>
    class BASILISK_API Shape
    {
    public:
        virtual ~Shape() = default;

    protected:
        explicit Shape(bool isSolid);
        
        /// <summary>
        /// Initializes the vertices that will be used for drawing.
        /// </summary>
        virtual void SetVertices() = 0;
        virtual void SetIndices() = 0;
        bool IsSolid;
    };
} // basilisk 
