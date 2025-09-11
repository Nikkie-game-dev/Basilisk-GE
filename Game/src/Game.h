#pragma once
#include "Basilisk/BaseGame.h"
#include "Basilisk/Renderer.h"
#include "Square.h"


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

        Square Test;
    };
}
