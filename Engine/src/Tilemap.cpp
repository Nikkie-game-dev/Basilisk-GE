#include "Tilemap.h"

#include <fstream>
#include <vector>

#include "Tile.h"

namespace basilisk
{

    TileMap::TileMap(const path& mapFilePath,
                     const path& texturePath,
                     const glm::vec2& textureSize,
                     const Filters filter,
                     const FitMode fitMode)
    {

        std::ifstream file(mapFilePath.string(), std::ios::in);

        this->Texture = TextureImporter::MakeTexture(texturePath.string(), filter, fitMode);
        this->Data = json::parse(file);
        this->TileSize = this->Data[this->TileSizeName];
        this->TilesAmount = {this->Data[MapWidthName], this->Data[MapHeightName]};

        this->PathToTexture = texturePath;
        this->TextureSize = textureSize;

        GenerateFrames();
        GenerateTiles();
    }

    void TileMap::Draw()
    {
        TextureImporter::BindTexture(this->Texture);

        for (int i = this->Tiles.size() - 1; i >= 0; --i)
        {
            for (auto& tile : this->Tiles.at(i))
            {
                tile.Draw();
            }
        }

        TextureImporter::UnbindTexture();
    }

    void TileMap::GenerateFrames()
    {
        const short cols = static_cast<short>(this->TextureSize.x / this->TileSize);
        const short rows = static_cast<short>(this->TextureSize.y / this->TileSize);

        this->SpriteSheetFrames.resize(cols * rows);
        int id = 0;

        for (int row = 0; row < rows; row++)
        {
            const float y = this->TextureSize.y - this->TileSize * (static_cast<float>(row) + 1);

            for (int col = 0; col < cols; col++)
            {
                const float x = this->TileSize * static_cast<float>(col);

                const auto frame = Frame({x, y}, {this->TileSize, this->TileSize}, this->TextureSize);
                this->SpriteSheetFrames.at(id) = frame;
                id++;
            }
        }
    }

    void TileMap::GenerateTiles()
    {
        auto mat = Material::New(true);

        const auto layersAmount = this->Data[LayersName].size();
        
        auto tileCount = 0;

        this->Tiles.resize(layersAmount);

        for (size_t layer = 0; layer < layersAmount; layer++)
        {
            const auto tilesAmount = this->Data[LayersName][layer][tileName].size();
            this->Tiles[layer].reserve(tilesAmount);

            for (size_t tile = 0; tile < tilesAmount; tile++)
            {
                const auto& tileJson = this->Data[LayersName][layer][tileName][tile];

                const std::string idStr = tileJson[IdName];
                const short id = stoi(idStr);
                const short row = tileJson[RowName];
                const short col = tileJson[ColName];


                this->Tiles[layer].emplace_back(this->SpriteSheetFrames.at(id), col, row);

                this->Tiles[layer].at(tileCount).SetMaterial(mat);
                this->Tiles[layer].at(tileCount).Init();

                this->Tiles[layer].at(tileCount).SetPosition({this->TileSize * static_cast<float>(col),
                                                              this->TileSize * (static_cast<float>(this->Data[MapHeightName]) - row)});
                
                this->Tiles[layer].at(tileCount).SetScaling({this->TileSize, this->TileSize});

                ++tileCount;
            }
            tileCount = 0;
        }
    }
} // namespace basilisk
