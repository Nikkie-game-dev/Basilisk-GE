#include "Tilemap.h"
#include <vector>
#include "Tile.h"

namespace basilisk
{
    TileMap::TileMap(path mapFilePath, glm::vec2 textureSize, glm::vec2 tileSize)
    {
        const auto tilesAmount = textureSize / tileSize;

        short cols = tilesAmount.x;
        short rows = tilesAmount.y;

        this->SpriteSheetFrames.reserve(cols * rows);

        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                const float x = tileSize.x * static_cast<float>(col);
                const float y = textureSize.y - tileSize.y * static_cast<float>(row);

                Frame frame = Frame({x, y}, tileSize, textureSize);
                this->SpriteSheetFrames.at(col) = frame;
            }
        }
    }
} // namespace basilisk
