#include "Frame.h"

namespace basilisk
{
    Frame::Frame(const glm::vec2& bottomLeft, const glm::vec2& frameSize, const glm::vec2& textureSize)
    {
        this->TopLeft = glm::vec2(bottomLeft.x, bottomLeft.y + frameSize.y) / textureSize;
        this->TopRight = glm::vec2(bottomLeft.x + frameSize.x, bottomLeft.y + frameSize.y) / textureSize;
        this->BottomLeft = bottomLeft / textureSize;
        this->BottomRight = glm::vec2(bottomLeft.x + frameSize.x, bottomLeft.y) / textureSize;
    }
} // namespace basilisk
