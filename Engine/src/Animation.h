#pragma once
#include <vector>
#include "glm/glm.hpp"

#include "Export.h"
#include "Frame.h"

namespace basilisk
{
    /// <summary>
    /// The Animation class. It provides functionality for 2D sprite animations.
    /// </summary>
    class BASILISK_API Animation
    {
    public:
        /// <summary>
        /// The constructor for Animation.
        /// </summary>
        Animation();

        /// <summary>
        /// Updates which frame is currently displaying.
        /// </summary>
        /// <param name="delta">Time between frames</param>
        /// <param name="outHasChanged">Returns true if an animation has changed frames</param>
        void Update(float delta, bool& outHasChanged);

        /// <summary>
        /// Sets the animation values. If you use an animation like this,
        /// the image of the sprite should be a spritesheet.
        /// </summary>
        /// <param name="frameBottomLeft">First frame bottom left coordinates</param>
        /// <param name="frameSize">Size (x = width, y = height) of one frame in pixels</param>
        /// <param name="textureSize">Size of the total texture in pixels</param>
        /// <param name="animationDuration">The duration of the entire animation in seconds</param>
        /// <param name="frameCount">Frame total amount (horizontal)</param>
        void GenUVFrames(const glm::vec2& frameBottomLeft,
                         const glm::vec2& frameSize,
                         const glm::vec2& textureSize,
                         const float& animationDuration,
                         const int& frameCount);

        /// <summary>
        /// Replaces frames vector and animation duration. It's useful when you need to manually define each frame.
        /// </summary>
        /// <param name="frames"></param>
        /// <param name="animationDuration"></param>
        void ReplaceFrames(const std::vector<Frame>& frames, const float& animationDuration);

        /// <summary>
        /// Returns current Frame
        /// </summary>
        /// <returns>Current Frame</returns>
        [[nodiscard]] Frame GetCurrentFrame() const;

        /// <summary>
        /// Enables update of animation.
        /// </summary>
        void Play();

        /// <summary>
        /// Disables update of animation
        /// </summary>
        void Pause();

        /// <summary>
        /// Disables update of animation and rests current frame to first frame.
        /// </summary>
        void Stop();

        /// <summary>
        /// Resets current frame to first frame without disabling update.
        /// </summary>
        void Reset();

        /// <summary>
        /// Getter for Animation Id.
        /// </summary>
        /// <returns>Animation Id</returns>
        [[nodiscard]] int GetId() const;

        /// <summary>
        /// Gets animation playing state.
        /// </summary>
        /// <returns>Whether the animation is playing</returns>
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
