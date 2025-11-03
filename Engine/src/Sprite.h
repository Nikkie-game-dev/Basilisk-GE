#pragma once
#include "Animation.h"
#include "Entity2D.h"

namespace basilisk
{
    class BASILISK_API Sprite : public Entity2D
    {
    public:
        explicit Sprite(const std::string& textureDir, glm::vec2 center, glm::vec2 size);
        ~Sprite();

        Sprite(const Sprite& Other); // copy constructor
        Sprite(Sprite&& Other) noexcept; // move constructor
        Sprite& operator=(const Sprite& Other); // copy assignment
        Sprite& operator=(Sprite&& Other) noexcept; // move assignment
        
        void Init() override;
        void UpdateAnim();

    private:
        unsigned int Texture;
        Animation* Anim = nullptr;
    };

} // namespace basilisk
