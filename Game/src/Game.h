#pragma once
#include "BaseGame.h"
#include "OrangeSquare.h"
#include "Renderer.h"


namespace game
{
    class Game : public basilisk::BaseGame
    {
    public:
        Game(const std::string& windowName, int sizeX, int sizeY);

    private:
        void Init() override;
        void Update() override;
        void Draw() override;

        OrangeSquare Test;
    };
}
