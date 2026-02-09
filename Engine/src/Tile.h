#pragma once
#include "Sprite.h"
#include "Square.h"

namespace basilisk
{
    class Tile final : public Entity2D
    {
    public:
        Tile(Frame frame, 
             short col, 
             short row);

        void Update() override;
        void Draw() override;

        bool HasCollision;
        short Col;
        short Row;
    };

} // namespace basilisk
