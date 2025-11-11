#include "TextureTest.h"

#include <iostream>

namespace game
{
    TextureTest::TextureTest()
        : Sprite(R"(res\assets\Trans-Flag-uwu.png)", {300,300} , {100, 100})
    {
    }
    void TextureTest::Update()
    {
        static bool goLeft = false;

        if (this->GetPosition2D().x < 100)
        {
            goLeft = true;
        }
        else if (this->GetPosition2D().x > 700)
        {
            goLeft = false;
        }
        
        auto pos = this->GetPosition2D();
        this->SetPosition({pos.x + (goLeft ? 100.0f * this->Delta : -100.0f * this->Delta), pos.y});
    }
}
