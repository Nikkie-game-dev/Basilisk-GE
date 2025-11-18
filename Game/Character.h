// 18/11/2025 - Basilisk-GE

#pragma once

#include "Basilisk/Sprite.h"
#include "Basilisk/InputAction.h"

namespace game
{
    using namespace basilisk;
    class Character final : public Sprite 
    {
    public:
        Character(const std::string& textureDir, const glm::vec2& center, const glm::vec2& size);
        void Update() override;

        
        basilisk::Animation AttackAnimation;
        basilisk::Animation IdleAnimation;
        basilisk::Animation DeathAnimation;
        
        basilisk::Animation* CurrentAnimation = nullptr;

        InputAction* Attack = nullptr;

        bool IsGettingAttacked = false;
        float Delta;
        float DeathTimer;
        float AttackTimer;
        float AccumulatorTime;
    };
} // game 
