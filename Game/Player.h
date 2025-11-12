#pragma once
#include "Basilisk/Sprite.h"
#include "InputAction.h"

namespace game
{
    class Player : public basilisk::Sprite
    {

    public:
        Player(float speed);
        void Update() override;
        void Init() override;
        float Delta;

        basilisk::InputAction* MoveUpIA = nullptr;
        basilisk::InputAction* MoveDownIA = nullptr;
        basilisk::InputAction* MoveLeftIA = nullptr;
        basilisk::InputAction* MoveRightIA = nullptr;

        basilisk::InputAction* ScaleUpIA = nullptr;
        basilisk::InputAction* ScaleDownIA = nullptr;
        basilisk::InputAction* RotateCWIA = nullptr;
        basilisk::InputAction* RotateCCWIA = nullptr;

    private:
        float Speed;
        void Move();
        void Scale();
        void Rotate();

        basilisk::Animation IdleAnimation;
        basilisk::Animation WalkUpAnimation;
        basilisk::Animation WalkDownAnimation;
        basilisk::Animation WalkHorAnimation;
        basilisk::Animation* CurrentAnimation = nullptr;
    };

} // namespace game
