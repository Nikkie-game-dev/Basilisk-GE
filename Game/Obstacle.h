#pragma once

#include "Basilisk/Sprite.h"
#include "Basilisk/Animation.h"

namespace game
{
    class Obstacle : public basilisk::Sprite
    {
    public:
        basilisk::Animation IdleAnimation;
        float Delta;

        Obstacle();

        void Update() override;
        void GetPushed(float speed);
    };
} // namespace game
