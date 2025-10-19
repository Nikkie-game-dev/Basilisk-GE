#pragma once
#include "Entity2D.h"

namespace basilisk
{
    class BASILISK_API Sprite : public Entity2D
    {
    public:
        explicit Sprite(const std::string& textureDir, glm::vec2 center, glm::vec2 size);
        void Init() override;

    private:
        unsigned int Texture;
    };

} // namespace basilisk
