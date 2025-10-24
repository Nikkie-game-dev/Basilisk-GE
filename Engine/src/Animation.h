#pragma once
#include <vector>
#include "glm/glm.hpp"

#include "Frame.h"

class Animation
{
public:
    void Update(float delta);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="frameCoord"></param>
    /// <param name="frameSize"></param>
    /// <param name="textureSize"></param>
    /// <param name="duration">Frame duration in seconds</param>
    void AddFrame(glm::vec2 frameCoord, glm::vec2 frameSize, 
                  glm::vec2 textureSize, float duration);

    void AddFrame(glm::vec2 frameCoord, glm::vec2 frameSize, 
                  glm::vec2 textureSize, float duration, 
                  int frameCount);

private:
    int CurrentFrame;
    float CurrentTime;
    float Length;
    std::vector<Frame> Frames;
};
