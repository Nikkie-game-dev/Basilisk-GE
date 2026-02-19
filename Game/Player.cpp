#include "Player.h"
#include "Basilisk/Animation.h"
#include "Basilisk/TextureImporter.h"

namespace game
{
    Player::Player(const float speed, const glm::vec2& size, const glm::vec2& pos) :
        Sprite("res/assets/character.png", pos, size, basilisk::Filters::NEAREST), Delta(0.0f), Speed(speed)
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

    void Player::Init()
    {
        this->IdleAnimation.Play();
        Sprite::Init();
    }

    void Player::Move()
    {
        glm::vec2 position = this->GetPosition2D();

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

        this->SetPosition(position);
    }

} // namespace game
