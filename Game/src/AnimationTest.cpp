#include "AnimationTest.h"

namespace game
{
    AnimationTest::AnimationTest() : 
        Sprite(R"(res\assets\Soldier-Walk.png)", {400, 300}, {100, 100})
    {
        this->Animation = new basilisk::Animation();

        this->Animation->SetAnimationValues({0, 0}, {100, 100}, {800, 100}, 0.2f, 8);

        SetAnimation(this->Animation);
    }

    AnimationTest::~AnimationTest()
    {
        delete Animation;
    }

    void AnimationTest::Update()
    {
        UpdateAnimation(Delta);
    }
} // namespace game
