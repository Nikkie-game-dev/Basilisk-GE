#include "Obstacle.h"
namespace game
{
    Obstacle::Obstacle() :
        Sprite("res/assets/Rock.jfif", glm::vec2(400.0f, 300.0f), glm::vec2(100.0f, 100.0f), basilisk::Filters::NEAREST)
    {
        this->IdleAnimation.GenUVFrames({76, 127}, {81, 56}, {244, 207}, 1.0f, 1);

        SetAnimation(&this->IdleAnimation);
    }

    void Obstacle::Update()
    {
        UpdateAnimation(this->Delta);
    }

    void Obstacle::GetPushed(float speed)
    {
        auto pos = GetPosition2D();
        pos.x += speed;

        this->SetPosition(pos);
    }
} // namespace game