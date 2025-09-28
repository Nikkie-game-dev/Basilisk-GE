
#pragma once
#include "Basilisk\Square.h"

namespace game
{
    class OrangeSquare final : public basilisk::Square
    {
    public:
        OrangeSquare(const glm::vec2& size, const glm::vec2& position, float rotation);
        OrangeSquare(const glm::vec2& size);
        void Update() override;

    };
} // game 
