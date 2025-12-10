#pragma once
#include "BaseGame.h"
#include "Tileset.h"

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
        TileSet Set;
    };

} // namespace game
