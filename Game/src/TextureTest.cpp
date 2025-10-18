#include "TextureTest.h"

namespace game
{
    TextureTest::TextureTest()
        : Sprite(R"(bin\Debug\res\Trans-Flag.png)", {300,300} , {100, 100})
    {
    }
    
    void TextureTest::Init()
    {
        Sprite::Init();
    }
    void TextureTest::Update()
    {
    }
}
