#pragma once
#include "Basilisk/Square.h"

namespace game
{
    class BlueSquare final : public basilisk::Square
    {
    public:
        explicit BlueSquare(glm::vec2 screenSize, float speed, float rotSpeed);
        void Update() override;

    private:
        float Speed;
        float RotSpeed;
        float Margin;
        glm::vec2 ScreenSize;
        glm::vec2 Size;
    };
} // game 
