#pragma once
#include "BaseGame.h"
#include "RedSquare.h"
#include "Player.h"
#include "BlueSquare.h"

namespace game
{
    class Game : public basilisk::BaseGame
    {
    public:
        Game(const char* windowName, float sizeX, float sizeY);
        ~Game() = default;
        void Init() override;
        void Update() override;
        void Draw() override;

    private:
        Player Player;
        RedSquare RedSquare;
        BlueSquare BlueSquare;
    };

} // namespace game
