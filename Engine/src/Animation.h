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
        
        Animation();
        
        void Update(float delta, bool& outHasChanged);

        /// <summary>
        /// Sets the animation values. If you use an animation like this,
        /// the image of the sprite should be a spritesheet.
        /// </summary>
        /// <param name="frameTopLeft">First frame top left coordinates</param>
        /// <param name="frameSize">Size (x = width, y = height) of one frame in pixels</param>
        /// <param name="textureSize">Size of the total texture in pixels</param>
        /// <param name="animationDuration">The duration of the entire animation in seconds</param>
        /// <param name="frameCount">Frame total amount (horizontal)</param>
        void GenUVFrames(const glm::vec2& frameTopLeft,
                                const glm::vec2& frameSize,
                                const glm::vec2& textureSize,
                                const float& animationDuration,
                                const int& frameCount);

        static Frame MakeFrame(const glm::vec2& topLeft, const glm::vec2& frameSize, const glm::vec2& textureSize);

        Frame GetCurrentFrame() const;
        
        void Play();
        
        void Pause();
        
        void Stop();
        
        void Reset();

        [[nodiscard]] int GetId() const;

        [[nodiscard]] bool IsAnimPlaying() const;

    private:
        int Id;
        int CurrentFrameIndex = -1;
        float ElapsedTimeMs = 0;
        float AnimationDurationMs = 0;
        std::vector<Frame> Frames;
        bool IsPlaying = false;
        
        static int IdsCounter;
    };

} // namespace basilisk
