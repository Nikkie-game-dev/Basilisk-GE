// 24/10/2025 - Basilisk-GE

#pragma once
#include "Basilisk/InputAction.h"
#include "Basilisk/Square.h"

namespace game
{
    class InputTest final : public basilisk::Square
    {
    public:
        InputTest(const glm::vec2& size, const glm::vec2& position);
        void Update() override;

        basilisk::InputAction* Action = nullptr;
    };
} // game 
