#pragma once

#include "Colors.h"
#include "Entity2D.h"
#include "Export.h"

namespace basilisk
{
    /// <summary>
    /// Abstract class for primitive shapes.
    /// </summary>
    class BASILISK_API Shape : public Entity2D
    {
    public:
        virtual ~Shape() = default;
        
        /// <summary>
        /// Initializes the shape. It overrides the Initialization function from Entity
        /// </summary>
        void Init() override;

    protected:
        explicit Shape(basilisk::Color color, bool isSolid);
        
        /// <summary>
        /// Initializes the vertices that will be used for drawing.
        /// </summary>
        virtual void SetVertices() = 0;
        bool IsSolid;
    };
} // basilisk 
