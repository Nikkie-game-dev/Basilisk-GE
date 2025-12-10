#include "Tileset.h"
#include <filesystem>

namespace game
{
    TileSet::TileSet(const glm::vec2& screenSize) : 
        TileMap("res/assets/map.json", "res/assets/spritesheet.png", {512, 1536}, screenSize)
    {
    }
} // namespace game
