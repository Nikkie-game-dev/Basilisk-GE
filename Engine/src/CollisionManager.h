#pragma once
#include "glm/vec2.hpp"

#include "Export.h"

namespace basilisk
{
    /// <summary>
    /// Manager for collisions.
    /// </summary>
    class BASILISK_API CollisionManager
    {
    public:
        /// <summary>
        /// Detects collisions.
        /// </summary>
        /// <param name="positionA">Center position of entity A</param>
        /// <param name="sizeA">Width and height of entity A</param>
        /// <param name="positionB">Center position of entity B</param>
        /// <param name="sizeB">Width and height of entity B</param>
        /// <returns>True if a collision is detected</returns>
        static bool IsCollidingAaBb(glm::vec2 positionA, glm::vec2 sizeA, glm::vec2 positionB, glm::vec2 sizeB);
    };
} // namespace basilisk 
