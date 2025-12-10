#include "Tileset.h"
#include <filesystem>

namespace game
{
    TileSet::TileSet() : 
        TileMap("res/assets/map.json", "res/assets/spritesheet.png", {512, 1536})
    {
    }
} // namespace game
