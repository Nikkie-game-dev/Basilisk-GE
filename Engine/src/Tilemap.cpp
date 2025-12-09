#include "Tilemap.h"

#include <fstream>
#include <vector>

#include "Tile.h"

namespace basilisk
{

    TileMap::TileMap(const path& mapFilePath, const path& texturePath, const glm::vec2& textureSize)
    {
        std::ifstream file(mapFilePath.string(), std::ios::in);

        this->Data = json::parse(file);
        this->TileSize = this->Data[this->TileSizeName];
        this->TilesAmount = {this->Data[MapWidthName], this->Data[MapHeightName]};

        this->PathToTexture = texturePath;
        this->TextureSize = textureSize;

        GenerateFrames();
        GenerateTiles();
    }

        short cols = textureSize.x / tileSize;
        short rows = textureSize.y / tileSize;
    void TileMap::GenerateFrames()
    {
        const short cols = static_cast<short>(this->TextureSize.x / this->TileSize);
        const short rows = static_cast<short>(this->TextureSize.y / this->TileSize);

        this->SpriteSheetFrames.reserve(cols * rows);

        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                const float x = this->TileSize * static_cast<float>(col);
                const float y = this->TilesAmount.y - this->TileSize * static_cast<float>(row);

                const auto frame = Frame({x, y}, {this->TileSize, this->TileSize}, this->TilesAmount);
                this->SpriteSheetFrames.at(col) = frame;
            }
        }
    }

    void TileMap::GenerateTiles()
    {
        const auto layersAmount = this->Data[LayersName].size();

        auto tileCount = 0;

        this->Tiles.resize(static_cast<size_t>(this->TilesAmount.x * this->TilesAmount.y));

        for (size_t layer = 0; layer < layersAmount; layer++)
        {
            for (size_t tile = 0; tile < this->Data[LayersName][layer].size(); tile++)
            {
                auto tileObj = this->Data[LayersName][layer][tile];
                const short id = tileObj[IdName];
                const short row = tileObj[RowName];
                const short col = tileObj[ColName];

                this->Tiles[layer].at(tileCount) = Tile(this->SpriteSheetFrames.at(id), col, row, this->PathToTexture.string(),
                                                        {this->TileSize, this->TileSize},
                                                        this->TextureSize);
                ++tileCount;
            }
        }
    }
} // namespace basilisk
