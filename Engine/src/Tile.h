#pragma once
#include "Sprite.h"

namespace basilisk
{
    class Tile final : public Entity2D
    {
    public:
        Tile(Frame frame,
             short col,
             short row);
        
        void Update() override;
        
        bool hasCollision;
        short Col;
        short Row;

    };

} // namespace basilisk
