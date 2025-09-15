
#pragma once
#include "../../Engine/src/Square.h"

namespace game
{
    class OrangeSquare final : public basilisk::Square
    {
    public:
        OrangeSquare(const glm::vec2& size, const glm::vec2& position, const float rotation);
        OrangeSquare(const glm::vec2& size);
        void Update() override;

    };
} // game 
