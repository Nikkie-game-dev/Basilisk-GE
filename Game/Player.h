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
        void Update() override;
        float Delta;

        //basilisk::InputAction* MoveUpIA = nullptr;
        //basilisk::InputAction* MoveDownIA = nullptr;
        basilisk::InputAction* MoveLeftIA = nullptr;
        basilisk::InputAction* MoveRightIA = nullptr;

        //basilisk::InputAction* ScaleUpIA = nullptr;
        //basilisk::InputAction* ScaleDownIA = nullptr;
        //basilisk::InputAction* RotateCWIA = nullptr;
        //basilisk::InputAction* RotateCCWIA = nullptr;
        
        glm::vec2 NextPos;
        void Move();
        float Speed;
        bool GetNextPos();
        basilisk::Animation IdleAnimation;

    private:
        void Scale();
        void Rotate();

        /*basilisk::Animation WalkUpAnimation;
        basilisk::Animation WalkDownAnimation;*/
        basilisk::Animation WalkHorAnimation;
    };

} // namespace game
