#pragma once
#include <vector>
#include "glm/glm.hpp"

#include "Frame.h"
#include "Export.h"

namespace basilisk
{
    enum Corners
    {
        TOP_RIGHT,
        TOP_LEFT,
        BOTTOM_RIGHT,
        BOTTOM_LEFT
    };

    class BASILISK_API Animation
    {
    public:
        void Update(float delta);

        /// <summary>
        /// Adds all the frames that the animation needs.
        /// </summary>
        /// <param name="frameCoord">First frame coord</param>
        /// <param name="frameSize">Size of one frame in pixels</param>
        /// <param name="textureSize">Size of the total texture in pixels</param>
        /// <param name="duration">Frame duration in seconds</param>
        void AddFrame(glm::vec2 frameCoord, glm::vec2 frameSize, glm::vec2 textureSize, float duration, int frameCount);

        Frame GetCurrentFrame();

    private:
        int CurrentFrame;
        float CurrentTime;
        float Length;
        std::vector<Frame> Frames;
    };

} // namespace basilisk
