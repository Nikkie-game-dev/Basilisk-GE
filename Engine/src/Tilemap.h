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
                const glm::vec2& screenSize,
                Filters filter = Filters::NEAREST,
                FitMode fitMode = FitMode::REPEAT,
                const glm::vec2& textureSize = {-1.0f, -1.0f});

        ~TileMap();
        void Init();
        void Draw();
        [[nodiscard]] float GetTileSize() const;
        CollisionManager::CollisionData CheckCollision(const Entity2D& entity);
        glm::ivec2 ConvertToTileMapPos(const glm::vec2& pos) const;
        glm::vec2 ConvertToScreenPos(const glm::ivec2& pos) const;

        class CollisionBox : public Square
        {
        public:
            CollisionBox(glm::vec2 center, glm::vec2 size, basilisk::Color color);

            void Update() override;
        };

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

        void GenerateFrames();
        void GenerateTiles();

        std::vector<std::vector<std::vector<Tile*>>> Tiles;
        std::vector<Frame> SpriteSheetFrames;

        unsigned int Texture;
        float TileSize;

        path PathToTexture;

        json Data;

        CollisionBox PlayerCollision;

        glm::ivec2 TextureSize;
        glm::ivec2 TilesAmount;
        glm::ivec2 ScreenSize;

        static const Key Keys;
    };

} // namespace basilisk
