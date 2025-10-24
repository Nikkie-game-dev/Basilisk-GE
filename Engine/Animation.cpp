#include "Animation.h"

void Animation::Update(float delta)
{
    CurrentTime += delta;

    while (CurrentTime > Length)
    {
        CurrentTime -= Length;
    }

    float frameLength = Length / Frames.size();

    CurrentFrame = static_cast<int>(CurrentTime / frameLength);
}

void Animation::AddFrame(glm::vec2 frameCoord, glm::vec2 frameSize, glm::vec2 textureSize, float duration)
{
    AddFrame(frameCoord, frameSize, textureSize, duration, 1);
}
void Animation::AddFrame(glm::vec2 frameCoord, glm::vec2 frameSize, glm::vec2 textureSize, float duration, int frameCount)
{
    Length = duration * 1000;

    float currentXPos = 0;

    for (int i = 0; i < frameCount; i++)
    {
        Frame frame;
        frame.coords[0].u = (frameCoord.x + currentXPos) / textureSize.x;
        frame.coords[0].v = frameCoord.y / textureSize.y;

        frame.coords[1].u = (frameCoord.x + currentXPos + frameSize.x) / textureSize.x;
        frame.coords[1].v = frame.coords[0].v;

        frame.coords[2].u = frame.coords[0].u;
        frame.coords[2].v = (frameCoord.y + frameSize.y + currentXPos) / textureSize.y;

        frame.coords[3].u = frame.coords[1].u;
        frame.coords[3].v = frame.coords[2].v;

        Frames.push_back(frame);

        currentXPos += frameSize.x;
    }
}
