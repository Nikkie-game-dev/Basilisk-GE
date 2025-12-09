#pragma once
#include <filesystem>

#include "Frame.h"
#include "Tile.h"
#include "glm/glm.hpp"
#include "json.hpp"

namespace basilisk
{
    using namespace std::filesystem;
    using json = nlohmann::json;

    class TileMap
    {
    public:
        TileMap(const path& mapFilePath, const path& texturePath, const glm::vec2& textureSize);
        void Draw() const;
        

    private:
        
        void GenerateFrames();
        void GenerateTiles();

        std::vector<std::vector<Tile>> Tiles;
        std::vector<Frame> SpriteSheetFrames;

        float TileSize;
        
        path PathToTexture;

        json Data;
        
        glm::vec2 TextureSize;
        glm::vec2 TilesAmount;
        
        std::string TileSizeName = "tileSize";
        std::string MapWidthName = "mapWidth";
        std::string MapHeightName = "mapHeight";
        std::string LayersName = "layers";
        std::string IdName = "id";
        std::string ColName = "x";
        std::string RowName = "y";

    };

} // namespace basilisk
