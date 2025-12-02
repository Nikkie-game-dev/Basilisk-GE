// 02/12/2025 - Basilisk-GE

#pragma once
#include <InputAction.h>

#include <Square.h>

namespace game
{
    class Obstacle final : public basilisk::Square
    {
    public:
        Obstacle();
        void Update() override;

        basilisk::InputAction* Shrink;
        basilisk::InputAction* Grow;
        basilisk::InputAction* RotateCW;
        basilisk::InputAction* RotateCCW;

        float Delta = 0;

    private:
        float Speed = 70;
        
    };
} // game 
