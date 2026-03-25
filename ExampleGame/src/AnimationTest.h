#pragma once
#include "Sprite.h"

namespace game
{
    class AnimationTest final : public basilisk::Sprite
    {
    public:
        AnimationTest();
        ~AnimationTest();
        void Update() override;

        float Delta = 0;

    private:
        basilisk::Animation* Animation;
    };

} // namespace game
