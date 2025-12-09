#pragma once
#include <filesystem>
#include "Frame.h"
#include "Tile.h"
#include "glm/glm.hpp"

namespace basilisk
{
    using namespace std::filesystem;

    class TileMap
    {
    public:
        TileMap(const path mapFilePath,
                const glm::vec2 textureSize,
                const std::string tileSizeName,
                const std::string mapWidthName,
                const std::string mapHeightName,
                const std::string layersName,
                const std::string idName,
                const std::string colName,
                const std::string rowName);

    private:
        std::vector<Tile> Tiles;
        std::vector<Frame> SpriteSheetFrames;
    };

} // namespace basilisk
