#pragma once
#include <TileMap.h>

#include "Basilisk/Sprite.h"
#include "InputAction.h"

namespace game
{
    class Player : public basilisk::Sprite
    {

    public:
        Player(float speed, float rotSpeed, const glm::vec2& size, const glm::vec2& pos);
        void Init() override;
        void Update() override;
        float Delta;

        basilisk::InputAction* MoveUpIA = nullptr;
        basilisk::InputAction* MoveDownIA = nullptr;
        basilisk::InputAction* MoveLeftIA = nullptr;
        basilisk::InputAction* MoveRightIA = nullptr;
        basilisk::InputAction* MoveBack = nullptr;
        basilisk::InputAction* MoveFront = nullptr;
        basilisk::InputAction* RotateLeft = nullptr;
        basilisk::InputAction* RotateRight = nullptr;

    private:
        void Move();

        float Speed;
        float RotSpeed;
        basilisk::Animation IdleAnimation;
        basilisk::Animation WalkUpAnimation;
        basilisk::Animation WalkDownAnimation;
        basilisk::Animation WalkHorAnimation;

    };

} // namespace game
