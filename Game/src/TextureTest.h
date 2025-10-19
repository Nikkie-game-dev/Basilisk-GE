// 18/10/2025 - Basilisk-GE

#pragma once
#include "Basilisk/Sprite.h"

namespace game
{
    class TextureTest final : public basilisk::Sprite
    {
    public:
        TextureTest();
        
        void Init() override;
        void Update() override;

    };
} // namespace game 
