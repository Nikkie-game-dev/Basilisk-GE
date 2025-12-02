// 02/12/2025 - Basilisk-GE

#pragma once
#include "Basilisk/Square.h"

namespace game
{
    class TransparentObs final : public basilisk::Square
    {
    public:
        TransparentObs(glm::vec2 screenSize);
        void Update() override;
        
        float Delta = 0;

    private:
        float Speed = 150.0f;
        bool GoLeft = false;
        glm::vec2 ScreenSize;
    };
} // game 
