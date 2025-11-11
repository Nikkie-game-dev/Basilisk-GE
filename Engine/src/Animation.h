#pragma once
#include <vector>
#include "glm/glm.hpp"

#include "Export.h"

namespace basilisk
{

    class BASILISK_API Animation
    {
    public:
        struct Frame
        {
            glm::vec2 topLeftUV;
            glm::vec2 topRightUV;
            glm::vec2 bottomLeftUV;
            glm::vec2 bottomRightUV;
        };
        void Update(float delta);

        /// <summary>
        /// Sets the animation values. If you use an animation like this,
        /// the image of the sprite should be a spritesheet.
        /// </summary>
        /// <param name="firstTopLeft">First frame top left coordinates</param>
        /// <param name="frameSize">Size (x = width, y = height) of one frame in pixels</param>
        /// <param name="textureSize">Size of the total texture in pixels</param>
        /// <param name="duration">The duration of the entire animation in seconds</param>
        /// <param name="frameCount">Frame total amount (horizontal)</param>
        void GenUVFrames(const glm::vec2& firstTopLeft,
                                const glm::vec2& frameSize,
                                const glm::vec2& textureSize,
                                const float& duration,
                                const int& frameCount);

        Animation::Frame MakeFrame(const glm::vec2& topLeft, const glm::vec2& frameSize, const glm::vec2& textureSize) const;

        Frame GetCurrentFrame();

    private:
        int CurrentFrameIndex;
        float ElapsedTime;
        float AnimationDuration;
        std::vector<Frame> Frames;
    };

} // namespace basilisk
