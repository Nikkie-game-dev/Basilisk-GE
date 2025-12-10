#pragma once
#include "glm/glm.hpp"

namespace basilisk
{
    class Frame
    {
    public:
        Frame() = default;
        
        /// <summary>
        /// Constructs a frame with a given size.
        /// </summary>
        /// <param name="bottomLeft">Bottom left coordinate of the frame in pixels, not uv.</param>
        /// <param name="frameSize">Size of the frame (x = width, y = height)</param>
        /// <param name="textureSize">Size of the texture (x = width, y = height)</param>
        Frame(const glm::vec2& bottomLeft, const glm::vec2& frameSize, const glm::vec2& textureSize);

        glm::vec2 TopLeft;
        glm::vec2 TopRight;
        glm::vec2 BottomLeft;
        glm::vec2 BottomRight;
    };

} // namespace basilisk
