
#pragma once
#include "../../Engine/src/Shape.h"

namespace game
{
    class OrangeSquare final : public basilisk::Shape
    {
    public:
        OrangeSquare(const glm::vec2& size, const glm::vec2& position, const glm::vec2& rotation);
        OrangeSquare(const glm::vec2& size);
        void Update() override;

    };
} // game 
