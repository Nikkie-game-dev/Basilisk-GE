#include "Animation.h"

namespace basilisk
{

    void Animation::Update(float deltaTime)
    {
        this->ElapsedTime = fmodf(ElapsedTime + deltaTime, this->AnimationDuration);

        if (this->ElapsedTime < 0.0f)
            this->ElapsedTime += this->AnimationDuration;

        float frameDuration = this->AnimationDuration / this->Frames.size();

        this->CurrentFrameIndex = static_cast<int>(this->ElapsedTime / frameDuration);
    }

    void Animation::GenUVFrames(const glm::vec2& frameTopLeft,
                                       const glm::vec2& frameSize,
                                       const glm::vec2& textureSize,
                                       const float& animationDuration,
                                       const int& frameCount)
    {
        this->AnimationDuration = animationDuration * 1000;
        this->Frames.reserve(frameCount);

        for (int i = 0; i < frameCount; i++)
        {
            const float x = frameTopLeft.x + frameSize.x * i;
            const float y = frameTopLeft.y;

            Frame frame = MakeFrame({x, y}, frameSize, textureSize);
            this->Frames.push_back(frame);
        }
    }

    Animation::Frame Animation::MakeFrame(const glm::vec2& topLeftPixels, const glm::vec2& frameSize, const glm::vec2& textureSize) const
    {
        Frame frame{};
        frame.topLeftUV = glm::vec2(topLeftPixels.x, topLeftPixels.y + frameSize.y) / textureSize;
        frame.topRightUV = glm::vec2(topLeftPixels.x + frameSize.x, frame.topLeftUV.y) / textureSize;
        frame.bottomLeftUV = topLeftPixels / textureSize;
        frame.bottomRightUV = glm::vec2(frame.topRightUV.x, frame.bottomLeftUV.y) / textureSize;

        return frame;
    }

    Animation::Frame Animation::GetCurrentFrame()
    {
        return this->Frames.at(this->CurrentFrameIndex);
    }

} // namespace basilisk
