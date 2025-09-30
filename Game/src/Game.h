#pragma once
#include "Basilisk/BaseGame.h"
#include "BlueSquare.h"

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

        BlueSquare Blue;
    };
}
