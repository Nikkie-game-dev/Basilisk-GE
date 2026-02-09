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
                Filters filter = Filters::NEAREST,
                FitMode fitMode = FitMode::REPEAT);
        ~TileMap();
        void Init();
        void Draw();
        float GetTileSize() const;
        CollisionManager::CollisionData CheckCollision(Entity2D& entity);

        class CollisionBox : public Square
        {
        public:
            CollisionBox(glm::vec2 center, glm::vec2 size, basilisk::Color color);

            void Update() override;
        };
    private:

        void GenerateFrames();
        void GenerateTiles();
        Tile* BuildTile(const std::shared_ptr<Material>& mat, glm::vec2 scale, const bool collider, const short id, const short row, const short col);
        glm::ivec2 ConvertToTileMapPos(const glm::vec2& pos);
        glm::vec2 ConvertToScreenPos(const glm::ivec2 pos);

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


        std::string TileSizeName = "tileSize";
        std::string MapWidthName = "mapWidth";
        std::string MapHeightName = "mapHeight";
        std::string LayersName = "layers";
        std::string IdName = "id";
        std::string ColName = "x";
        std::string RowName = "y";
        std::string tileName = "tiles";
        std::string colliderName = "collider";

    };

} // namespace basilisk
