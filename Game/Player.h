#pragma once
#include "Basilisk/Sprite.h"
#include "Basilisk/CollisionManager.h"
#include "InputAction.h"

namespace game
{
    class Player : public basilisk::Sprite
    {

    public:
        Player(const float speed, const glm::vec2& size, const glm::vec2& pos);
        void Init() override;
        void Update() override;
        void CheckCollision(basilisk::CollisionManager::CollisionData data);
        float Delta;

        basilisk::InputAction* MoveUpIA = nullptr;
        basilisk::InputAction* MoveDownIA = nullptr;
        basilisk::InputAction* MoveLeftIA = nullptr;
        basilisk::InputAction* MoveRightIA = nullptr;

        glm::vec2 PreviousPos;

    private:
        void Move();

        float Speed;
        basilisk::Animation IdleAnimation;
        basilisk::Animation WalkUpAnimation;
        basilisk::Animation WalkDownAnimation;
        basilisk::Animation WalkHorAnimation;
    };

} // namespace game
