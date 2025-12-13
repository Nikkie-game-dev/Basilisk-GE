#include "Tilemap.h"

#include <fstream>
#include <vector>
#include <iostream>

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
    }

    TileMap::~TileMap()
    {
        for (auto layer : this->Tiles)
        {
            for (const auto tile : layer)
            {
                delete tile;
            }
        }
    }

    void TileMap::Init()
    {
        GenerateFrames();
        GenerateTiles();
    }

    void TileMap::Draw() const
    {
        TextureImporter::BindTexture(this->Texture);

        for (int i = this->Tiles.size() - 1; i >= 0; --i)
        {
            for (const auto tile : this->Tiles.at(i))
            {
                if (tile)
                {
                    tile->Draw();
                }
            }
        }

        TextureImporter::UnbindTexture();
    }

    float TileMap::GetTileSize() const
    {
        return TileSize;
    }

    CollisionManager::CollisionData TileMap::CheckCollision(Entity2D& entity)
    {
        const auto& entityPos = entity.GetPosition2D();
        const auto& entityScale = entity.GetScale2D();

        glm::vec2 topLeftCorner = {entityPos.x - entityScale.x / 2, entityPos.y + entityScale.y / 2};
        glm::vec2 bottomRightCorner = {entityPos.x + entityScale.x / 2, entityPos.y - entityScale.y / 2};

        if (bottomRightCorner.x >= ScreenSize.x)
            bottomRightCorner.x = ScreenSize.x - 1.0f;

        if (bottomRightCorner.y >= ScreenSize.y)
            bottomRightCorner.y = ScreenSize.y - 1.0f;

        if (topLeftCorner.x < 0)
            topLeftCorner.x = 0;

        if (topLeftCorner.y < 0)
            topLeftCorner.y = 0;

        const glm::ivec2 topLeft = ConvertToTileMapPos(topLeftCorner);
        const glm::ivec2 bottomRight = ConvertToTileMapPos(bottomRightCorner);

        for (const auto& layer : this->Tiles)
        {
            for (int row = topLeft.y; row > bottomRight.y; row--)
            {
                for (int col = topLeft.x; col < bottomRight.x; col++)
                {
                    const auto currentTile = static_cast<size_t>(row * this->TilesAmount.x + col);

                    if (layer.size() <= currentTile)
                        continue;

                    if (const auto& tile = layer.at(currentTile); tile && tile->hasCollision)
                    {

                        return CollisionManager::GetCollisionDir(tile->GetPosition2D(), tile->GetScale2D(),
                                                                 entityPos, entityScale);
                    }
                }
            }
        }

        return {.VerticalDir = CollisionManager::CollisionDir::NONE, .HorizontalDir = CollisionManager::CollisionDir::NONE};
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

        const size_t layerSize = static_cast<size_t>(TilesAmount.x * TilesAmount.y);

        this->Tiles.resize(layersAmount);

        glm::vec2 scale = {std::ceil(this->ScreenSize.x / this->TilesAmount.x), std::ceil(this->ScreenSize.y / this->TilesAmount.y)};

        for (size_t layer = 0; layer < layersAmount; layer++)
        {
            const auto layerObj = this->Data[LayersName][layer];

            const bool collider = layerObj[colliderName];
            this->Tiles[layer].reserve(layerSize);

            for (size_t tile = 0; tile < layerSize; tile++)
            {
                if (layerObj[tileName].size() <= tile)
                {
                    this->Tiles[layer].push_back(nullptr);
                    continue;
                }

                const auto& tileJson = layerObj[tileName][tile];

                const std::string idStr = tileJson[IdName];
                const short id = stoi(idStr);
                const short row = tileJson[RowName];
                const short col = tileJson[ColName];

                this->Tiles[layer].push_back(BuildTile(mat, scale, collider, id, row, col));

                ++tileCount;
            }
            tileCount = 0;
        }
    }

    Tile* TileMap::BuildTile(const std::shared_ptr<Material>& mat,
                             const glm::vec2 scale,
                             const bool collider,
                             const short id,
                             const short row,
                             const short col)
    {
        const auto currentTile = new Tile(this->SpriteSheetFrames.at(id), col, row);
        currentTile->SetMaterial(mat);
        currentTile->Init();
        currentTile->SetPosition({scale.x * (static_cast<float>(col) + 0.5f),
                                  scale.y * (static_cast<float>(this->Data[MapHeightName]) - static_cast<float>(row) - 0.5f)});
        currentTile->SetScaling(scale);
        currentTile->hasCollision = collider;
        return currentTile;
    }

    glm::ivec2 TileMap::ConvertToTileMapPos(const glm::vec2& pos)
    {
        const glm::vec2 newPos = {pos.x / ScreenSize.x * this->TilesAmount.x, pos.y / ScreenSize.y * this->TilesAmount.y};

        return {round(newPos.x), round(newPos.y)};
    }

} // namespace basilisk
