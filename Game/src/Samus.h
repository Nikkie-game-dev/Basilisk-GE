// 02/12/2025 - Basilisk-GE

#pragma once
#include <InputAction.h>
#include <Sprite.h>

namespace game
{
    class Samus final : public basilisk::Sprite
    {
    public:
        Samus();
        void Update() override;
        
        basilisk::InputAction* WalkLeft;
        basilisk::InputAction* WalkRight;
        basilisk::InputAction* WalkDown;
        basilisk::InputAction* WalkUp;

        glm::vec2 NewPosition;
        glm::vec2 OldPosition;

        float Delta = 0;

    private:
        basilisk::Animation IdleAnim;
        basilisk::Animation LeftAnim;
        basilisk::Animation* CurrentAnimation;
        basilisk::Animation* OldAnimation;


        float Speed = 500.0f;
        
        bool WasWalking = false;
    };
} // game 
