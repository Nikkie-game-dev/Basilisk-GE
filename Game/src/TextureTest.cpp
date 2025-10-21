#include "TextureTest.h"

namespace game
{
    TextureTest::TextureTest() :
        Sprite(R"(bin\Debug\res\Trans-Flag.png)", {300, 300}, {100, 100})
    {
    }

    void TextureTest::Init()
    {
        Sprite::Init();
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
        this->SetPosition({pos.x + (goLeft ? 10.0f : -10.0f), pos.y});
    }
}
