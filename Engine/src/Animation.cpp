#include "Animation.h"

namespace basilisk
{

    void Animation::Update(float delta, bool& outHasChanged)
    {
        if (!this->IsPlaying) return;
        
        delta *= 1000;
        
        this->ElapsedTimeMs = fmodf(this->ElapsedTimeMs + delta, this->AnimationDurationMs);

        if (this->ElapsedTimeMs < 0.0f)
            this->ElapsedTimeMs += this->AnimationDurationMs;

        const float frameDurationMs = this->AnimationDurationMs / static_cast<float>(this->Frames.size());

        const int current = CurrentFrameIndex;
        this->CurrentFrameIndex = static_cast<int>(this->ElapsedTimeMs / frameDurationMs);
        
        outHasChanged = current != this->CurrentFrameIndex;
    }

    void Animation::GenUVFrames(const glm::vec2& frameTopLeft,
                                       const glm::vec2& frameSize,
                                       const glm::vec2& textureSize,
                                       const float& animationDuration,
                                       const int& frameCount)
    {
        this->AnimationDurationMs = animationDuration * 1000;
        this->Frames.reserve(frameCount);

        for (int i = 0; i < frameCount; i++)
        {
            const float x = frameTopLeft.x + frameSize.x * static_cast<float>(i);
            const float y = frameTopLeft.y;

            Frame frame = MakeFrame({x, y}, frameSize, textureSize);
            this->Frames.push_back(frame);
        }
    }

    Animation::Frame Animation::MakeFrame(const glm::vec2& topLeft, const glm::vec2& frameSize, const glm::vec2& textureSize)
    {
        Frame frame;
        
        frame.topLeftUV = glm::vec2(topLeft.x, topLeft.y + frameSize.y) / textureSize;
        frame.topRightUV = glm::vec2(topLeft.x + frameSize.x, topLeft.y + frameSize.y) / textureSize;
        frame.bottomLeftUV = topLeft / textureSize;
        frame.bottomRightUV = glm::vec2(topLeft.x + frameSize.x, topLeft.y) / textureSize;

        return frame;
    }

    Animation::Frame Animation::GetCurrentFrame() const
    {
        return this->Frames.at(this->CurrentFrameIndex);
    }
    
    void Animation::Play()
    {
        this->IsPlaying = true;
    }
    
    void Animation::Pause()
    {
        this->IsPlaying = false;
    }

    void Animation::Stop()
    {
        this->IsPlaying = false;
        this->Reset();
    }
    
    void Animation::Reset()
    {
        this->ElapsedTimeMs = 0;
    }

    bool Animation::IsAnimPlaying() const
    {
        return this->IsPlaying;
    }

} // namespace basilisk
