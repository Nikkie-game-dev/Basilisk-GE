#include "Animation.h"

namespace basilisk
{

    void Animation::Update(float delta)
    {
        this->CurrentTime += delta;

        while (this->CurrentTime > this->Length)
        {
            this->CurrentTime -= this->Length;
        }

        float frameLength = this->Length / this->Frames.size();

        this->CurrentFrame = static_cast<int>(this->CurrentTime / frameLength);
    }

    void Animation::AddFrame(glm::vec2 frameCoord, glm::vec2 frameSize, glm::vec2 textureSize, float duration, int frameCount)
    {
        this->Length = duration * 1000;

        float currentXPos = 0;

        for (int i = 0; i < frameCount; i++)
        {
            Frame frame;
            frame.coords[BOTTOM_LEFT].u = (frameCoord.x + currentXPos) / textureSize.x;
            frame.coords[BOTTOM_LEFT].v = frameCoord.y / textureSize.y;

            frame.coords[BOTTOM_RIGHT].u = (frameCoord.x + currentXPos + frameSize.x) / textureSize.x;
            frame.coords[BOTTOM_RIGHT].v = frame.coords[BOTTOM_LEFT].v;

            frame.coords[TOP_LEFT].u = frame.coords[BOTTOM_LEFT].u;
            frame.coords[TOP_LEFT].v = (frameCoord.y + frameSize.y + currentXPos) / textureSize.y;

            frame.coords[TOP_RIGHT].u = frame.coords[TOP_LEFT].u;
            frame.coords[TOP_RIGHT].v = frame.coords[TOP_LEFT].v;

            this->Frames.push_back(frame);

            currentXPos += frameSize.x;
        }
    }

    Frame Animation::GetCurrentFrame()
    {
        return this->Frames.at(this->CurrentFrame);
    }

} // namespace basilisk
