#pragma once
#include "BaseGame.h"
#include "Basilisk/TileMap.h"
#include "Player.h"

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
        basilisk::TileMap Map;
        Player Player;
    };

} // namespace game
