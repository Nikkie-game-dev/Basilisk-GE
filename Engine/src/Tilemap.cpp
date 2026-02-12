#include "Tilemap.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "Tile.h"

namespace basilisk
{

    const TileMap::Key TileMap::Keys = TileMap::Key();

    TileMap::TileMap(const path& mapFilePath,
                     const path& texturePath,
                     const glm::vec2& textureSize,
                     const glm::vec2& screenSize,
                     const Filters filter,
                     const FitMode fitMode) : PlayerCollision({0, 0}, {1, 1}, Color::Red)

    {

        std::ifstream file(mapFilePath.string(), std::ios::in);

        this->Texture = TextureImporter::MakeTexture(texturePath.string(), filter, fitMode);
        this->Data = json::parse(file);
        this->TileSize = this->Data[Keys.TileSize];
        this->TilesAmount = {this->Data[Keys.MapWidth], this->Data[Keys.MapHeight]};

        this->PathToTexture = texturePath;
        this->TextureSize = textureSize;
        this->ScreenSize = screenSize;

        auto collisionMat = Material::New(false);

        PlayerCollision.SetMaterial(collisionMat);
    }

    TileMap::~TileMap()
    {
        for (auto layer : this->Tiles)
        {
            for (auto row : layer)
            {
                for (auto col : row)
                {
                    delete col;
                }
            }
        }
    }

    void TileMap::Init()
    {
        this->GenerateFrames();
        this->GenerateTiles();
        PlayerCollision.Init();
    }

    void TileMap::Draw()
    {
        TextureImporter::BindTexture(this->Texture);


        for (int layer = this->Tiles.size() - 1; layer >= 0; --layer)
        {
            for (auto row : this->Tiles[layer])
            {
                for (auto col : row)
                {
                    if (col)
                    {
                        col->Draw();
                    }
                }
            }
        }

        TextureImporter::UnbindTexture();
        PlayerCollision.Draw();
    }

    float TileMap::GetTileSize() const
    {
        return TileSize;
    }

    CollisionManager::CollisionData TileMap::CheckCollision(Entity2D& entity)
    {
        CollisionManager::CollisionData noneCollision = {.VerticalDir = CollisionManager::CollisionDir::NONE,
                                                         .HorizontalDir = CollisionManager::CollisionDir::NONE};
        const auto& entityPos = entity.GetPosition2D();
        const auto& entityScale = entity.GetScale2D();

        glm::vec2 topLeftCorner = {entityPos.x - entityScale.x / 2, entityPos.y + entityScale.y / 2};
        glm::vec2 bottomRightCorner = {entityPos.x + entityScale.x / 2, entityPos.y - entityScale.y / 2};

        // Clamp corners to screen bounds
        {
            if (bottomRightCorner.y < 0)
                bottomRightCorner.y = 0;

            if (bottomRightCorner.x < 0)
                bottomRightCorner.x = 0;

            if (bottomRightCorner.y >= ScreenSize.y)
                bottomRightCorner.y = ScreenSize.y - 1.0f;

            if (bottomRightCorner.x >= ScreenSize.x)
                bottomRightCorner.x = ScreenSize.x - 1.0f;

            if (topLeftCorner.x >= ScreenSize.x)
                topLeftCorner.x = ScreenSize.x - 1.0f;

            if (topLeftCorner.y >= ScreenSize.y)
                topLeftCorner.y = ScreenSize.y - 1.0f;

            if (topLeftCorner.y < 0)
                topLeftCorner.y = 0;

            if (topLeftCorner.x < 0)
                topLeftCorner.x = 0;
        }

        glm::ivec2 topLeft = this->ConvertToTileMapPos(topLeftCorner);

        glm::ivec2 bottomRight = this->ConvertToTileMapPos(bottomRightCorner);

        PlayerCollision.SetPosition(entityPos);

        glm::vec2 size = {bottomRightCorner.x - topLeftCorner.x, topLeftCorner.y - bottomRightCorner.y};

        PlayerCollision.SetScaling(size);

        const glm::vec2 tilePos = {entityPos.x / 1920 * 29, entityPos.y / 900 * 16};

        Tile* lastTile = nullptr;
        Tile* firstTileCollided = nullptr;

        for (const auto& layer : this->Tiles)
        {
            for (int row = topLeft.y; row < bottomRight.y; row++)
            for (int row = topLeft.y; row <= bottomRight.y; row++)
            {
                for (int col = topLeft.x; col <= bottomRight.x; col++)
                {
                    if (const auto& tile = layer[row][col]; tile && tile->HasCollision)
                    {
                        auto data = CollisionManager::GetCollisionDir(tile->GetPosition2D(), tile->GetScale2D(), entityPos, entityScale);
                        data.CollisionTilePos = {col, row};
                        return data;
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
        auto commonMat = Material::New(true, false);
        auto debugMat = Material::New(true, true);

        const auto layersAmount = this->Data[Keys.Layers].size();

        auto tileCount = 0;

        this->Tiles.resize(layersAmount);

        int layerSize = this->TilesAmount.x * this->TilesAmount.y;

        glm::vec2 scale = {std::ceil(this->ScreenSize.x / this->TilesAmount.x), std::ceil(this->ScreenSize.y / this->TilesAmount.y)};

        short id;
        short row;
        short col;
        std::string layer;

        for (size_t layer = 0; layer < layersAmount; layer++)
        {
            const auto layerObj = this->Data[Keys.Layers][layer];
            const std::string layerStr = layerObj[Keys.Layer];

            const bool collider = layerObj[Keys.Collider];

            this->Tiles[layer].resize(TilesAmount.y);

            for (int rows = 0; rows < TilesAmount.y; rows++)
            {
                this->Tiles[layer][rows].resize(TilesAmount.x);

                for (int cols = 0; cols < TilesAmount.x; cols++)
                {
                    this->Tiles[layer][rows][cols] = nullptr;
                }
            }

            for (int tileId = 0; tileId < layerObj[Keys.Tile].size(); tileId++)
            {
                const auto& tileJson = layerObj[Keys.Tile][tileId];

                const std::string idStr = tileJson[Keys.Id];
                id = stoi(idStr);
                row = tileJson[Keys.Row];
                col = tileJson[Keys.Col];
                const bool collider = layerObj[this->Keys.Collider];

                this->Tiles[layer][row][col] = new Tile(this->SpriteSheetFrames.at(id), col, row);

                auto currentTile = this->Tiles[layer][row][col];

                currentTile->SetMaterial(collider ? debugMat : commonMat);
                currentTile->Init();
                currentTile->SetPosition({scale.x * (static_cast<float>(col) + 0.5f),
                                          scale.y * (static_cast<float>(this->Data[Keys.MapHeight]) - static_cast<float>(row) - 0.5f)});
                currentTile->SetScaling(scale);
                currentTile->HasCollision = collider;
                currentTile->LayerName = layerStr;
            }
        }
    }

    glm::ivec2 TileMap::ConvertToTileMapPos(const glm::vec2& pos)
    {
        const glm::vec2 newPos = {pos.x / ScreenSize.x * this->TilesAmount.x,
                                  this->TilesAmount.y - (pos.y / ScreenSize.y * this->TilesAmount.y)};

        return {static_cast<int>(newPos.x), static_cast<int>(newPos.y)};
    }

    glm::vec2 TileMap::ConvertToScreenPos(const glm::ivec2 pos)
    {
        const glm::vec2 newPos = {pos.x * ScreenSize.x / TilesAmount.x, pos.y * ScreenSize.y / TilesAmount.y};
        return newPos;
    }

    TileMap::CollisionBox::CollisionBox(glm::vec2 center, glm::vec2 size, basilisk::Color color) : Square(center, size, true, color)
    {
    }

    void TileMap::CollisionBox::Update()
    {
    }

} // namespace basilisk
