#include "Player.h"
#include "Basilisk/Animation.h"

namespace game
{
    Player::Player() : basilisk::Sprite("res/assets/character.png", glm::vec2(300.0f, 300.0f), glm::vec2(100.0f, 100.0f))
    {
        this->IdleAnimation.GenUVFrames({0, 11 * 32}, {32, 32}, {128, 384}, 1.0f, 2);
        SetAnimation(&this->IdleAnimation);
    }

    void Player::Update()
    {
        UpdateAnimation(this->Delta);
    }

} // namespace game
