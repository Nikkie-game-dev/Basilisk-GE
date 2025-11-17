#pragma once

#include "Basilisk/Square.h"

namespace game
{
    class Obstacle : public basilisk::Square
    {
    public:
        Obstacle();

        void Update() override;
    };
} // namespace game
