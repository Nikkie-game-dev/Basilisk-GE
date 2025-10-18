#pragma once
#include "Entity2D.h"

namespace basilisk
{
    class Sprite : public Entity2D
    {
    public:
        explicit Sprite(const std::string& textureDir);
        
    private:
        unsigned int Texture;
    };

} // namespace basilisk
