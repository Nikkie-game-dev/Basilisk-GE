#pragma once
#include "Basilisk/Sprite.h"
#include "InputAction.h"

namespace game
{
    class Player : public basilisk::Sprite
    {

    public:
        explicit Player(float speed);
        void Init() override;
        bool GetNextPos();
        void Update() override;
        float Delta;

        basilisk::InputAction* MoveLeftIA = nullptr;
        basilisk::InputAction* MoveRightIA = nullptr;

        basilisk::InputAction* SpinIA = nullptr;
        basilisk::InputAction* PushIA = nullptr;

        basilisk::Animation CollisionAnimation;
        basilisk::Animation IdleAnimation;
        
        glm::vec2 NextPos;
        void Move();
        float Speed;

    private:

        basilisk::Animation WalkHorAnimation;
        basilisk::Animation SpinAnimation;
    };

} // namespace game
