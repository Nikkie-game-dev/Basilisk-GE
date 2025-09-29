#pragma once

#include "Colors.h"
#include "Entity2D.h"
#include "Export.h"

namespace basilisk
{

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
        /// Calculates the positions of each vertex of the shape.
        /// </summary>
        /// <param name="center">The center of the shape</param>
        /// <param name="size">The size (x = width and y = height) of the shape</param>
        virtual void CalculateVertices(glm::vec2 center, glm::vec2 size) = 0;
        /// <summary>
        /// Initializes the vertices that will be used for drawing.
        /// </summary>
        virtual void SetVertices() = 0;
        bool IsSolid;
    };
} // basilisk 
