#include "Tileset.h"
#include <filesystem>

namespace game
{
    TileSet::TileSet() : 
        basilisk::TileMap(std::filesystem::path("res/assets/map.json"), std::filesystem::path("res/assets/spritesheet.png"), {512, 1536})
    {

    }
} // namespace game
