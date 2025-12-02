#include "Player.h"
#include "Basilisk/Animation.h"
#include "Basilisk/TextureImporter.h"

namespace game
{
    /// <summary>
    /// Cuadrado rojo con collider y q samus choque y tiene que responder a inputs, 
    /// que haga todas las transformaciones menos movimiento.
    /// </summary>
    /// <param name="speed"></param>

    Player::Player(const float speed) :
        Sprite(
            "res/assets/Samus Aran Sprite Sheet.png", 
            glm::vec2(200.0f, 300.0f), 
            glm::vec2(100.0f, 100.0f), 
            basilisk::Filters::NEAREST
            ),
        Delta(0.0f), Speed(speed)
    {
        this->IdleAnimation.GenUVFrames({24, 7 * 95.25}, {66, 64}, {860, 762}, 1.0f, 5);
        this->WalkHorAnimation.GenUVFrames({14, 5 * 98}, {82, 64}, {860, 762}, 1.0f, 10);

        this->NextPos = this->GetPosition2D();

        SetAnimation(&this->IdleAnimation);
    }

    void Player::Update()
    {
        UpdateAnimation(this->Delta);
    }

    void Player::Init()
    {
        this->IdleAnimation.Play();
        Sprite::Init();
    }

    void Player::Move()
    {
        this->SetPosition(NextPos);
    }

    bool Player::GetNextPos()
    {
        bool moved = false;

        glm::vec2 position = this->GetPosition2D();

        if (this->MoveLeftIA && this->MoveLeftIA->IsDown())
        {
            FlipSpriteX = false;
            ChangeAnimation(&WalkHorAnimation);
            position.x -= this->Speed * this->Delta;
            moved = true;
        }
        else if (this->MoveRightIA && this->MoveRightIA->IsDown())
        {
            FlipSpriteX = true;
            ChangeAnimation(&WalkHorAnimation);
            position.x += this->Speed * this->Delta;
            moved = true;
        }

        if (moved)
            this->NextPos = position;

        return moved;
    }


    //void Player::Scale()
    //{
    //    glm::vec2 scale = this->GetScale2D();

    //    if (this->ScaleUpIA && this->ScaleUpIA->IsDown())
    //    {
    //        scale.x += this->Speed * this->Delta;
    //        scale.y += this->Speed * this->Delta;
    //    }

    //    else if (this->ScaleDownIA && this->ScaleDownIA->IsDown())
    //    {
    //        if (scale.x - this->Speed * this->Delta <= 0.0f ||
    //            scale.y - this->Speed * this->Delta <= 0.0f)
    //        {
    //            return;
    //        }

    //        scale.x -= this->Speed * this->Delta;
    //        scale.y -= this->Speed * this->Delta;
    //    }

    //    this->SetScaling(scale);
    //}

  /*  void Player::Rotate()
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
    }*/

} // namespace game
