#pragma once
#include "Sprite.h"
#include "Square.h"
#include <string>

namespace basilisk
{
    class Tile final : public Shape, public Entity2D
    {
    public:
        Tile(const Frame& frame, 
             short col, 
             short row);

        void Update() override;
        short Col;
        short Row;
        bool HasCollision;
        std::string LayerName;

    protected:
        void SetVertices() override;
        void SetIndices() override;

    private:
        Frame Frame;

       
    };

} // namespace basilisk
