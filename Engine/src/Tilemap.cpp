#include "Tilemap.h"

#include <fstream>
#include <vector>
#include "json.hpp"

#include "Tile.h"

namespace basilisk
{
    using json = nlohmann::json;

    TileMap::TileMap(const path mapFilePath,
                     const glm::vec2 textureSize,
                     const std::string tileSizeName = "tileSize",
                     const std::string mapWidthName = "mapWidth",
                     const std::string mapHeightName = "mapHeight",
                     const std::string layersName = "layers",
                     const std::string idName = "id",
                     const std::string colName = "x",
                     const std::string rowName = "y"
    )
    {
        std::ifstream file(mapFilePath.string(), std::ios::in);

        json data = json::parse(file);

        int tileSize = data[tileSizeName];
        glm::vec2 tilesAmount = {data[mapWidthName], data[mapHeightName]};

        short cols = textureSize.x / tileSize;
        short rows = textureSize.y / tileSize;

        this->SpriteSheetFrames.reserve(cols * rows);

        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                const float x = tileSize * static_cast<float>(col);
                const float y = tilesAmount.y - tileSize * static_cast<float>(row);

                Frame frame = Frame({x, y}, {tileSize,tileSize}, tilesAmount);
                this->SpriteSheetFrames.at(col) = frame;
            }
        }

        auto layersAmount = data[layersName].size();

        auto tileCount = 0;

        this->Tiles.reserve(tilesAmount.x * tilesAmount.y);

        for (int layer = 0; layer < layersAmount; layer++)
        {
            for (int tile = 0; tile < data[layersName][layer].size(); tile++)
            {
                auto tileObj = data[layersName][layer][tile];
                short id = tileObj[idName];
                short row = tileObj[rowName];
                short col = tileObj[colName];

                this->Tiles.at(tileCount) = Tile(id, col, row);
            }
        }
    }
} // namespace basilisk
