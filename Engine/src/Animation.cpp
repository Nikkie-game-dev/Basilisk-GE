#include "Animation.h"

#include <iostream>

namespace basilisk
{
    int Animation::IdsCounter = 0;

    Animation::Animation()
    {
        this->Id = IdsCounter;
        IdsCounter++;
    }

    void Animation::Update(float delta, bool& outHasChanged)
    {
        if (!this->IsPlaying)
            return;

        delta *= 1000;

        this->ElapsedTimeMs = fmodf(this->ElapsedTimeMs + delta, this->AnimationDurationMs);

        if (this->ElapsedTimeMs < 0.0f)
            this->ElapsedTimeMs += this->AnimationDurationMs;

        const float frameDurationMs = this->AnimationDurationMs / static_cast<float>(this->Frames.size());

        const int current = CurrentFrameIndex;
        this->CurrentFrameIndex = static_cast<int>(this->ElapsedTimeMs / frameDurationMs);

        outHasChanged = current != this->CurrentFrameIndex;
    }

    void Animation::GenUVFrames(const glm::vec2& frameBottomLeft,
                                const glm::vec2& frameSize,
                                const glm::vec2& textureSize,
                                const float& animationDuration,
                                const int& frameCount)
    {
        this->AnimationDurationMs = animationDuration * 1000;
        this->Frames.reserve(frameCount);

        for (int i = 0; i < frameCount; i++)
        {
            const float x = frameBottomLeft.x + frameSize.x * static_cast<float>(i);
            const float y = frameBottomLeft.y;

            Frame frame = MakeFrame({x, y}, frameSize, textureSize);
            this->Frames.push_back(frame);
        }
    }

    Animation::Frame Animation::MakeFrame(const glm::vec2& bottomLeft, const glm::vec2& frameSize, const glm::vec2& textureSize)
    {
        Frame frame;

        frame.topLeftUV = glm::vec2(bottomLeft.x, bottomLeft.y + frameSize.y) / textureSize;
        frame.topRightUV = glm::vec2(bottomLeft.x + frameSize.x, bottomLeft.y + frameSize.y) / textureSize;
        frame.bottomLeftUV = bottomLeft / textureSize;
        frame.bottomRightUV = glm::vec2(bottomLeft.x + frameSize.x, bottomLeft.y) / textureSize;

        return frame;
    }

    Animation::Frame Animation::GetCurrentFrame() const
    {
        return this->Frames.at(this->CurrentFrameIndex == -1 ? 0 : this->CurrentFrameIndex);
    }

    void Animation::Play()
    {

#ifdef CONSOLE_OUTPUT_ENABLED
        std::cout << "Animation playing. ID: " << this->Id << ". Address: " << this << "/n";
#endif

        this->IsPlaying = true;
    }

    void Animation::Pause()
    {
#ifdef CONSOLE_OUTPUT_ENABLED
        std::cout << "Animation pausing. ID: " << this->Id << ". Address: " << this << "/n";
#endif

        this->IsPlaying = false;
    }

    void Animation::Stop()
    {
#ifdef CONSOLE_OUTPUT_ENABLED
        std::cout << "Animation stopping. ID: " << this->Id << ". Address: " << this << "/n";
#endif

        this->IsPlaying = false;
        this->Reset();
    }

    void Animation::Reset()
    {
#ifdef CONSOLE_OUTPUT_ENABLED
        std::cout << "Animation resetting. ID: " << this->Id << ". Address: " << this << "/n";
#endif

        this->ElapsedTimeMs = 0;
    }

    int Animation::GetId() const
    {
        return this->Id;
    }

    bool Animation::IsAnimPlaying() const
    {
        return this->IsPlaying;
    }

} // namespace basilisk
