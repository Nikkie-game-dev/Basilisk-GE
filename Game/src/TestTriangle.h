
#pragma once
#include "Basilisk/Triangle.h"
#include "Basilisk/Square.h"

namespace game
{
    class TestTriangle final : public basilisk::Triangle
    {
    public:
        TestTriangle(const glm::vec2& size, const glm::vec2& position);
        void Update() override;

    };
} // game 
