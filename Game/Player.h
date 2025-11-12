#pragma once
#include "Basilisk/Sprite.h"

namespace game
{
    class Player : public basilisk::Sprite
    {

    public:
        Player();
        void Update() override;
        float Delta;
        basilisk::Animation IdleAnimation;
    };

} // namespace game
