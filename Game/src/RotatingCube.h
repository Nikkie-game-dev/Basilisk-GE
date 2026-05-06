// 29/04/2026 - Basilisk-GE

#pragma once
#include "Basilisk/Cube.h"

namespace game
{
    class RotatingCube final : public basilisk::Cube
    {
    public:
        RotatingCube(bool isSolid, const glm::vec3& center, const glm::vec3& size, const basilisk::Color& color) :
            Cube(isSolid, center, size, color)
        {
        }
        
        void Update() override;

    };
} // game 
