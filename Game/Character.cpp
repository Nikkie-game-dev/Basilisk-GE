#include "Character.h"
#include "Basilisk/Input.h"

namespace game
{
    Character::Character(const std::string& textureDir, const glm::vec2& center, const glm::vec2& size) :
        Sprite(textureDir, center, size)
    {
    }
    
    void Character::Update()
    {
        if (this->IsGettingAttacked && this->CurrentAnimation != &this->DeathAnimation)
        {
            this->ChangeAnimation(&this->DeathAnimation);
            this->CurrentAnimation = &this->DeathAnimation;
            this->DeathTime = 0;
        }
        else if (this->CurrentAnimation == &this->DeathAnimation)
        {
            this->DeathTime += this->Delta;

            if (this->DeathTime >= this->DeathTimer)
            {
                this->ChangeAnimation(&this->IdleAnimation);
                this->CurrentAnimation = &this->IdleAnimation;
            }
        }
        else if (this->Attack->IsPressedAndReleased() && this->CurrentAnimation == &this->IdleAnimation)
        {
            this->ChangeAnimation(&this->AttackAnimation);
            this->CurrentAnimation = &this->AttackAnimation;
        }
        else
        {
            this->ChangeAnimation(&this->IdleAnimation);
            this->CurrentAnimation = &this->IdleAnimation;
        }

        this->UpdateAnimation(this->Delta);
    }
}
