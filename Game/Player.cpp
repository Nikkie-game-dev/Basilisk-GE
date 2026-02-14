#include "Player.h"
#include "Basilisk/Animation.h"
#include "Basilisk/TextureImporter.h"

namespace game
{
    Player::Player(const float speed, const glm::vec2& size) :
        Sprite("res/assets/character.png", glm::vec2(600.0f, 200.0f), size, basilisk::Filters::NEAREST), Delta(0.0f), Speed(speed)
    {
        this->IdleAnimation.GenUVFrames({0, 11 * 32}, {32, 32}, {128, 384}, 1.0f, 2);
        this->WalkUpAnimation.GenUVFrames({0, 6 * 32}, {32, 32}, {128, 384}, 1.0f, 4);
        this->WalkHorAnimation.GenUVFrames({0, 7 * 32}, {32, 32}, {128, 384}, 1.0f, 4);
        this->WalkDownAnimation.GenUVFrames({0, 8 * 32}, {32, 32}, {128, 384}, 1.0f, 4);

        SetAnimation(&this->IdleAnimation);
    }

    void Player::Update()
    {
        Move();
        UpdateAnimation(this->Delta);
    }

    void Player::CheckCollision(basilisk::CollisionManager::CollisionData data)
    {
        if (data.HorizontalDir == basilisk::CollisionManager::CollisionDir::NONE &&
            data.VerticalDir == basilisk::CollisionManager::CollisionDir::NONE)
            return;

        glm::vec2 newPos = GetPosition2D();

        if (data.HorizontalDir != basilisk::CollisionManager::CollisionDir::NONE)
            newPos.x = PreviousPos.x;

        if (data.VerticalDir != basilisk::CollisionManager::CollisionDir::NONE)
        {
            switch (data.VerticalDir)
            {
            case basilisk::CollisionManager::CollisionDir::UP:
                newPos.y = PreviousPos.y + 0.2f;
                break;
            case basilisk::CollisionManager::CollisionDir::DOWN:
                newPos.y = PreviousPos.y - 0.2f;
                break;
            default:
                break;
            }
        }

        SetPosition(newPos);
    }

    void Player::Init()
    {
        this->IdleAnimation.Play();
        Sprite::Init();
    }

    void Player::Move()
    {
        glm::vec2 position = this->GetPosition2D();
        glm::vec2 previousPos = position;

        if (this->MoveUpIA && this->MoveUpIA->IsDown())
        {
            ChangeAnimation(&this->WalkUpAnimation);
            position.y += this->Speed * this->Delta;
        }

        else if (this->MoveDownIA && this->MoveDownIA->IsDown())
        {
            ChangeAnimation(&this->WalkDownAnimation);
            position.y -= this->Speed * this->Delta;
        }

        else if (this->MoveLeftIA && this->MoveLeftIA->IsDown())
        {
            this->FlipSpriteX = true;
            ChangeAnimation(&this->WalkHorAnimation);
            position.x -= this->Speed * this->Delta;
        }

        else if (MoveRightIA && this->MoveRightIA->IsDown())
        {
            this->FlipSpriteX = false;
            ChangeAnimation(&this->WalkHorAnimation);
            position.x += this->Speed * this->Delta;
        }

        else
        {
            ChangeAnimation(&this->IdleAnimation);
        }

        if (position != previousPos)
            this->PreviousPos = previousPos;

        this->SetPosition(position);
    }

} // namespace game
