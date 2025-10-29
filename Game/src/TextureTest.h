// 18/10/2025 - Basilisk-GE

#pragma once
#include "Basilisk/Sprite.h"

namespace game
{
    class TextureTest final : public basilisk::Sprite
    {
    public:
        TextureTest();
        void Update() override;

        float Delta = 0;

    };
} // namespace game 
