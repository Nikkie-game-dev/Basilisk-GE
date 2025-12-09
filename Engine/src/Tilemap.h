#pragma once
#include <filesystem>
#include "glm/glm.hpp"
#include "Frame.h"

namespace basilisk
{
    using namespace std::filesystem;

    class TileMap
    {
    public:
        TileMap(path mapFilePath, glm::vec2 textureSize, glm::vec2 tileSize);

    private:
        std::vector<Tile> Tiles;
        std::vector<Frame> SpritesheetFrames;
    };

} // namespace basilisk
