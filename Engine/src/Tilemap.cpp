#include "Tilemap.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "Tile.h"

#define NONE_COLLISION {.VerticalDir = CollisionManager::CollisionDir::NONE, .HorizontalDir = CollisionManager::CollisionDir::NONE}

namespace basilisk
{

    const TileMap::Key TileMap::Keys = {
        .TileSize = "tileSize",
        .MapWidth = "mapWidth",
        .MapHeight = "mapHeight",
        .Layers = "layers",
        .Id = "id",
        .Col = "x",
        .Row = "y",
        .Tile = "tiles",
        .Collider = "collider",
        .Layer = "name",
    };

    TileMap::TileMap(const path& mapFilePath,
                     const path& texturePath,
                     const glm::vec2& textureSize,
                     const glm::vec2& screenSize,
                     const Filters filter,
                     const FitMode fitMode) :
        PlayerCollision({0, 0}, {1, 1}, Color::Red)

    {

        std::ifstream file(mapFilePath.string(), std::ios::in);

        this->Texture = TextureImporter::MakeTexture(texturePath.string(), filter, fitMode);
        this->Data = json::parse(file);
        this->TileSize = this->Data[Keys.TileSize];
        this->TilesAmount = {this->Data[Keys.MapWidth], this->Data[Keys.MapHeight]};

        this->PathToTexture = texturePath;
        this->TextureSize = textureSize;
        this->ScreenSize = screenSize;

        const auto collisionMat = Material::New(false);

        PlayerCollision.SetMaterial(collisionMat);
    }

    TileMap::~TileMap()
    {
        for (const auto& layer : this->Tiles)
        {
            for (const auto& row : layer)
            {
                for (const auto col : row)
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


        for (int layer = static_cast<int>(this->Tiles.size()) - 1; layer >= 0; --layer)
        {
            for (const auto& row : this->Tiles[layer])
            {
                for (const auto col : row)
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

    CollisionManager::CollisionData TileMap::CheckCollision(const Entity2D& entity)
    {
        const auto& entityPos = entity.GetPosition2D();
        const auto& entityScale = entity.GetScale2D();

        glm::vec2 topLeftCorner = {entityPos.x - entityScale.x / 2, entityPos.y + entityScale.y / 2};
        glm::vec2 bottomRightCorner = {entityPos.x + entityScale.x / 2, entityPos.y - entityScale.y / 2};


        // Clamp corners to screen bounds
        {
            bottomRightCorner.y = std::max<float>(bottomRightCorner.y, 0);

            bottomRightCorner.x = std::max<float>(bottomRightCorner.x, 0);

            if (bottomRightCorner.y >= static_cast<float>(ScreenSize.y))
                bottomRightCorner.y = static_cast<float>(ScreenSize.y) - 1.0f;

            if (bottomRightCorner.x >= static_cast<float>(ScreenSize.x))
                bottomRightCorner.x = static_cast<float>(ScreenSize.x) - 1.0f;

            if (topLeftCorner.x >= static_cast<float>(ScreenSize.x))
                topLeftCorner.x = static_cast<float>(ScreenSize.x) - 1.0f;

            if (topLeftCorner.y >= static_cast<float>(ScreenSize.y))
                topLeftCorner.y = static_cast<float>(ScreenSize.y) - 1.0f;

            topLeftCorner.y = std::max<float>(topLeftCorner.y, 0);

            topLeftCorner.x = std::max<float>(topLeftCorner.x, 0);
        }

        const glm::ivec2 topLeftTilePos = this->ConvertToTileMapPos(topLeftCorner);
        const glm::ivec2 bottomRightTilePos = this->ConvertToTileMapPos(bottomRightCorner);

        PlayerCollision.SetPosition(entityPos);

        const glm::vec2 collisionBoxSize = {bottomRightCorner.x - topLeftCorner.x, topLeftCorner.y - bottomRightCorner.y};

        PlayerCollision.SetScaling(collisionBoxSize);

        std::list<glm::ivec2> checkedTiles;

        for (const auto& layer : this->Tiles)
        {
            for (int row = topLeftTilePos.y; row <= bottomRightTilePos.y; row++)
            {
                for (int col = topLeftTilePos.x; col <= bottomRightTilePos.x; col++)
                {
                    bool wasTileChecked = false;

                    for (const auto& checkedTilePos : checkedTiles)
                    {
                        if (checkedTilePos.x == col && checkedTilePos.y == row)
                        {
                            wasTileChecked = true;
                            break;
                        }
                    }

                    if (wasTileChecked)
                        continue;

                    const auto& tile = layer[row][col];

                    if (tile && tile->HasCollision)
                    {
                        auto data = CollisionManager::GetCollisionDir(tile->GetPosition2D(), entityPos);
                        data.CollisionTilePos = {tile->Col, tile->Row};
                        data.CollisionLayer = tile->LayerName;
                        return data;
                    }

                    if (tile)
                    {
                        checkedTiles.emplace_back(col, row);
                    }
                }
            }
        }

        return NONE_COLLISION;
    }

    void TileMap::GenerateFrames()
    {
        const short cols = static_cast<short>(this->TextureSize.x / this->TileSize);
        const short rows = static_cast<short>(this->TextureSize.y / this->TileSize);

        this->SpriteSheetFrames.resize(cols * rows);
        int id = 0;

        for (int row = 0; row < rows; row++)
        {
            const float y = static_cast<float>(this->TextureSize.y) - this->TileSize * (static_cast<float>(row) + 1);

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
        const auto commonMat = Material::New(true, false);
        const auto debugMat = Material::New(true, true);

        const auto layersAmount = this->Data[Keys.Layers].size();

        this->Tiles.resize(layersAmount);

        const glm::vec2 scale = {std::ceil(this->ScreenSize.x / this->TilesAmount.x), std::ceil(this->ScreenSize.y / this->TilesAmount.y)};

        short id;
        short row;
        short col;

        for (size_t layer = 0; layer < layersAmount; layer++)
        {
            const auto layerObj = this->Data[Keys.Layers][layer];
            const std::string layerStr = layerObj[Keys.Layer];

            this->Tiles[layer].resize(TilesAmount.y);

            for (int rows = 0; rows < TilesAmount.y; rows++)
            {
                this->Tiles[layer][rows].resize(TilesAmount.x);

                for (int cols = 0; cols < TilesAmount.x; cols++)
                {
                    this->Tiles[layer][rows][cols] = nullptr;
                }
            }

            for (int tileId = 0; tileId < static_cast<int>(layerObj[Keys.Tile].size()); tileId++)
            {
                const auto& tileJson = layerObj[Keys.Tile][tileId];

                const std::string idStr = tileJson[Keys.Id];
                id = static_cast<short>(stoi(idStr));
                row = tileJson[Keys.Row];
                col = tileJson[Keys.Col];
                const bool collider = layerObj[Keys.Collider];

                this->Tiles[layer][row][col] = new Tile(this->SpriteSheetFrames.at(id), col, row);

                const auto currentTile = this->Tiles[layer][row][col];

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

    glm::ivec2 TileMap::ConvertToTileMapPos(const glm::vec2& pos) const
    {
        const glm::vec2 newPos = {pos.x / static_cast<float>(this->ScreenSize.x * this->TilesAmount.x),
                                  static_cast<float>(this->TilesAmount.y) - pos.y / static_cast<float>(this->ScreenSize.y * this->
                                      TilesAmount.y)};

        return {static_cast<int>(newPos.x), static_cast<int>(newPos.y)};
    }

    glm::vec2 TileMap::ConvertToScreenPos(const glm::ivec2& pos) const
    {
        const glm::vec2 newPos = {pos.x * ScreenSize.x / TilesAmount.x, pos.y * ScreenSize.y / TilesAmount.y};
        return newPos;
    }

    TileMap::CollisionBox::CollisionBox(glm::vec2 center, glm::vec2 size, basilisk::Color color) :
        Square(center, size, true, color)
    {
    }

    void TileMap::CollisionBox::Update()
    {
    }

} // namespace basilisk
