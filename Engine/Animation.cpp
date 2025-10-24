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