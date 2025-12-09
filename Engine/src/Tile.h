#pragma once
#include "Sprite.h"

namespace basilisk
{
    class Tile final : public Sprite
    {
    public:
        Tile(Frame frame,
             short col,
             short row,
             const std::string& textureFilePath,
             glm::vec2 size,
             glm::vec2 textureSize,
             Filters filter = Filters::NEAREST,
             FitMode fitMode = FitMode::REPEAT);
        
        void Update() override = delete;

        short Col;
        short Row;
    };

} // namespace basilisk
