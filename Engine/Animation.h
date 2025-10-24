#pragma once
#include <vector>
#include "glm/glm.hpp"

#include "Frame.h"

class Animation
{
public:
    void Update(float delta);

private:
    int CurrentFrame;
    float CurrentTime;
    float Length;
    std::vector<Frame> Frames;
};
