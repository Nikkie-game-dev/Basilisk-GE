#include "Tilemap.h"

#include <fstream>
#include <vector>

#include "Tile.h"

namespace basilisk
{

    TileMap::TileMap(const path& mapFilePath,
                     const path& texturePath,
                     const glm::vec2& textureSize,
                     const glm::vec2& screenSize,
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
        this->ScreenSize = screenSize;

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

        glm::vec2 scale = {std::ceil(this->ScreenSize.x / this->TilesAmount.x), std::ceil(this->ScreenSize.y / this->TilesAmount.y)};

        for (size_t layer = 0; layer < layersAmount; layer++)
        {
            const auto layerObj = this->Data[LayersName][layer];

            const auto tilesAmount = layerObj[tileName].size();
            const bool collider = layerObj[colliderName];
            this->Tiles[layer].reserve(tilesAmount);

            for (size_t tile = 0; tile < tilesAmount; tile++)
            {
                const auto& tileJson = layerObj[tileName][tile];

                const std::string idStr = tileJson[IdName];
                const short id = stoi(idStr);
                const short row = tileJson[RowName];
                const short col = tileJson[ColName];


                this->Tiles[layer].emplace_back(this->SpriteSheetFrames.at(id), col, row);

                auto& currentTile = this->Tiles[layer].at(tileCount);

                currentTile.SetMaterial(mat);
                currentTile.Init();

                currentTile.SetPosition({scale.x * (static_cast<float>(col) + 0.5f),
                                         scale.y * (static_cast<float>(this->Data[MapHeightName]) - static_cast<float>(row) - 0.5f)});

                currentTile.SetScaling(scale);

                currentTile.hasCollision = collider;

                ++tileCount;
            }
            tileCount = 0;
        }
    }

    CollisionManager::CollisionData TileMap::CheckCollision(Entity2D& entity)
    {
        auto entityPos = entity.GetPosition2D();
        auto entityScale = entity.GetScale2D();

        glm::vec2 topLeftCorner = {entityPos.x, entityPos.y - entityScale.y / 2};
        glm::vec2 bottomRightCorner = {entityPos.x + entityScale.x / 2, entityPos.y + entityScale.y / 2};

        if (bottomRightCorner.x >= ScreenSize.x)
            bottomRightCorner.x = ScreenSize.x - 1.0f;

        if (bottomRightCorner.y >= ScreenSize.y)
            bottomRightCorner.y = ScreenSize.y - 1;

        if (topLeftCorner.x < 0)
            topLeftCorner.x = 0.0f;

        if (topLeftCorner.y < 0)
            topLeftCorner.y = 0;

        glm::ivec2 center = ConvertToTileMapPos(entityPos);
        glm::ivec2 topLeft = ConvertToTileMapPos(topLeftCorner);
        glm::ivec2 bottomRight = ConvertToTileMapPos(bottomRightCorner);

        for (int layer = 0; layer < this->Tiles.size(); layer++)
        {
            for (int row = topLeft.y; row < bottomRight.y; row++)
            {
                for (int col = topLeft.x; col < bottomRight.x; col++)
                {
                    auto tile = this->Tiles[layer].at(row * this->TilesAmount.x + col);

                    if (tile.hasCollision)
                    {
                        return CollisionManager::GetCollisionDir(tile.GetPosition2D(), tile.GetScale2D(), 
                                                                 entityPos, entityScale);
                    }
                }
            }
        }

        return {CollisionManager::CollisionDir::NONE, CollisionManager::CollisionDir::NONE};
    }

    glm::ivec2 TileMap::ConvertToTileMapPos(const glm::vec2& pos)
    {
        const glm::vec2 newPos = {pos.x / ScreenSize.x * this->TilesAmount.x, pos.y / ScreenSize.y * this->TilesAmount.y};

        return {ceil(newPos.x), ceil(newPos.y)};
    }

} // namespace basilisk
