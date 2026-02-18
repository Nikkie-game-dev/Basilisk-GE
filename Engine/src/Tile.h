#pragma once
#include "Sprite.h"
#include "Square.h"
#include <string>

namespace basilisk
{
    class Tile final : public Entity2D
    {
    public:
        Tile(const Frame& frame, 
             const short& col, 
             const short& row);

        void Update() override;
        void Draw() override;

        bool HasCollision;
        short Col;
        short Row;
        std::string LayerName;
    };

} // namespace basilisk
