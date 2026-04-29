#pragma once
#include "Frame.h"
#include "Tile.h"
#include "glm/glm.hpp"
#include "json.hpp"

#include "CollisionManager.h"

namespace basilisk
{
    using namespace std::filesystem;
    using json = nlohmann::json;

    class BASILISK_API TileMap
    {
    public:

        TileMap(const path& mapFilePath,
                const path& texturePath,
                const vec2& screenSize,
                Filters filter = Filters::NEAREST,
                FitMode fitMode = FitMode::REPEAT,
                const vec2& textureSize = {-1.0f, -1.0f});

        ~TileMap();
        void Init();
        void Draw() const;
        [[nodiscard]] float GetTileSize() const;
        CollisionManager::CollisionData CheckCollision(const vec2& entityPos, const vec2& entityScale) const;
        ivec2 ConvertToTileMapPos(const vec2& pos) const;
        vec2 ConvertToScreenPos(const ivec2& pos) const;

    private:
        struct Key
        {
            const std::string TileSize;
            const std::string MapWidth;
            const std::string MapHeight;
            const std::string Layers;
            const std::string Id;
            const std::string Col;
            const std::string Row;
            const std::string Tile;
            const std::string Collider;
            const std::string Layer;
        };
        void ClampCorners(vec2& topLeftCorner, vec2& bottomRightCorner) const;
        void GenerateFrames();
        void GenerateTiles();

        std::vector<std::vector<std::vector<Tile*>>> Tiles;
        std::vector<Frame> SpriteSheetFrames;

        unsigned int Texture;
        float TileSize;

        path PathToTexture;

        json Data;

        ivec2 TextureSize;
        ivec2 TilesAmount;
        ivec2 ScreenSize;

        static const Key Keys;
    };

} // namespace basilisk
