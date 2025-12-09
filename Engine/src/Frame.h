#pragma once
#include "glm/glm.hpp"

namespace basilisk
{
    class Frame
    {
    public:
        /// <summary>
        /// Constructs a frame with a given size.
        /// </summary>
        /// <param name="bottomLeft"></param>
        /// <param name="frameSize"></param>
        /// <param name="textureSize"></param>
        Frame(const glm::vec2& bottomLeft, const glm::vec2& frameSize, const glm::vec2& textureSize);

        glm::vec2 TopLeft;
        glm::vec2 TopRight;
        glm::vec2 BottomLeft;
        glm::vec2 BottomRight;
    };

} // namespace basilisk
