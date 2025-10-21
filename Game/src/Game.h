#pragma once
#include "Basilisk/BaseGame.h"
#include "TestTriangle.h"
#include "GreenSquare.h"
#include "Basilisk/Renderer.h"
#include "TextureTest.h"


namespace game
{
    class Game : public basilisk::BaseGame
    {
    public:
        Game(const char* windowName, int sizeX, int sizeY);

    private:
        void Init() override;
        void Update() override;
        void Draw() override;

        TestTriangle Test;
        GreenSquare Test2;
        TextureTest Test3;

    };
}
