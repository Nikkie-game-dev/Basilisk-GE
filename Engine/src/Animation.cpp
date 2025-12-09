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
        if (!this->IsPlaying || this->Frames.size() <= 1)
            return;

        delta *= 1000; // convert from seconds to milliseconds

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

            Frame frame = Frame({x, y}, frameSize, textureSize);
            this->Frames.at(i) = frame;
        }
    }

    void Animation::ReplaceFrames(std::vector<Frame> frames, const float animationDuration)
    {
        this->AnimationDurationMs = animationDuration * 1000;
        this->Frames = frames;
    }

    Frame Animation::GetCurrentFrame() const
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

        this->CurrentFrameIndex = 0;
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
