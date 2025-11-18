#include "Player.h"
#include "Basilisk/Animation.h"
#include "Basilisk/TextureImporter.h"

namespace game
{
    Player::Player(const float speed) :
        Sprite("res/assets/Knuckles.png", glm::vec2(300.0f, 300.0f), glm::vec2(100.0f, 100.0f), basilisk::Filters::NEAREST), Delta(0.0f),
        Speed(speed)
    {
        this->IdleAnimation.GenUVFrames({0, 15 * 29}, {36, 36}, {646, 473}, 1.0f, 1);
        this->WalkHorAnimation.GenUVFrames({41*2, 14 * 28}, {41, 36}, {646, 473}, 1.0f, 4);
        this->SpinAnimation.GenUVFrames({0, 12 * 26}, {33, 34}, {646, 473}, 1.0f, 6);
        this->CollisionAnimation.GenUVFrames({12 * 35.5, 13 * 26.5}, {35, 36}, {646, 473}, 1.0f, 4);

        this->NextPos = this->GetPosition2D();

        SetAnimation(&this->IdleAnimation);
    }

    void Player::Update()
    {
        Scale();
        Rotate();
        UpdateAnimation(this->Delta);

        if (this->SpinIA && this->SpinIA->IsDown())
        {
            ChangeAnimation(&SpinAnimation);
        }
        if (this->PushIA && this->PushIA->IsDown())
        {
            ChangeAnimation(&CollisionAnimation);
        }
    }

    void Player::Init()
    {
        this->IdleAnimation.Play();
        Sprite::Init();
    }

    bool Player::GetNextPos()
    {
        bool moved = false;

        glm::vec2 position = this->GetPosition2D();

        if (this->MoveLeftIA && this->MoveLeftIA->IsDown())
        {
            FlipSpriteX = true;
            ChangeAnimation(&WalkHorAnimation);
            position.x -= this->Speed * this->Delta;
            moved = true;
        }
        else if (this->MoveRightIA && this->MoveRightIA->IsDown())
        {
            FlipSpriteX = false;
            ChangeAnimation(&WalkHorAnimation);
            position.x += this->Speed * this->Delta;
            moved = true;
        }

        if (moved)
            this->NextPos = position;

        return moved;
    }

    void Player::Move()
    {
        this->SetPosition(NextPos);
    }

    void Player::BackToPreviousPos()
    {
    }

    void Player::Scale()
    {
        glm::vec2 scale = this->GetScale2D();

        if (this->ScaleUpIA && this->ScaleUpIA->IsDown())
        {
            scale.x += this->Speed * this->Delta;
            scale.y += this->Speed * this->Delta;
        }

        else if (this->ScaleDownIA && this->ScaleDownIA->IsDown())
        {
            if (scale.x - this->Speed * this->Delta <= 0.0f || scale.y - this->Speed * this->Delta <= 0.0f)
            {
                return;
            }

            scale.x -= this->Speed * this->Delta;
            scale.y -= this->Speed * this->Delta;
        }

        this->SetScaling(scale);
    }

    void Player::Rotate()
    {
        float rotation = this->GetRotation2D();

        if (RotateCWIA && RotateCWIA->IsDown())
        {
            rotation += this->Speed * this->Delta;
        }
        else if (RotateCCWIA && RotateCCWIA->IsDown())
        {
            rotation -= this->Speed * this->Delta;
        }

        SetRotation(rotation);
    }

} // namespace game
