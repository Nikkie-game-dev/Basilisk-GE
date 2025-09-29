#pragma once
#include "Basilisk/Square.h"

namespace game
{
    class GreenSquare : public basilisk::Square
    {
        GreenSquare(const glm::vec2& size, const glm::vec2& position, float rotation);
        GreenSquare(const glm::vec2& size);
        void Update() override;
    };
} // namespace game
