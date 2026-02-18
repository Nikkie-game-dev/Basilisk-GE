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
                const glm::vec2& textureSize,
                const glm::vec2& screenSize,
                const Filters filter = Filters::NEAREST,
                const FitMode fitMode = FitMode::REPEAT);
        ~TileMap();
        void Init();
        void Draw();
        float GetTileSize() const;
        CollisionManager::CollisionData CheckCollision(const Entity2D& entity);
        glm::ivec2 ConvertToTileMapPos(const glm::vec2& pos);
        glm::vec2 ConvertToScreenPos(const glm::ivec2& pos);

        class CollisionBox : public Square
        {
        public:
            CollisionBox(glm::vec2 center, glm::vec2 size, basilisk::Color color);

            void Update() override;
        };

    private:
        struct Key
        {
            const std::string TileSize = "tileSize";
            const std::string MapWidth = "mapWidth";
            const std::string MapHeight = "mapHeight";
            const std::string Layers = "layers";
            const std::string Id = "id";
            const std::string Col = "x";
            const std::string Row = "y";
            const std::string Tile = "tiles";
            const std::string Collider = "collider";
            const std::string Layer = "name";
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

        glm::vec2 TextureSize;
        glm::vec2 TilesAmount;
        glm::vec2 ScreenSize;

        static const Key Keys;
    };

} // namespace basilisk
