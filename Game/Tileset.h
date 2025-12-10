#pragma once
#include "Tilemap.h"

namespace game
{
    class TileSet : public basilisk::TileMap
    {
    public:
        TileSet(const glm::vec2& screenSize);
    };

} // namespace game
