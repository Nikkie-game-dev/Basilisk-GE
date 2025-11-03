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

        Sprite(const Sprite& other); // copy constructor
        Sprite(Sprite&& other) noexcept; // move constructor
        Sprite& operator=(const Sprite& other); // copy assignment
        Sprite& operator=(Sprite&& other) noexcept; // move assignment
        
        void Init() override;
        void UpdateAnim();

    private:
        unsigned int Texture;
        Animation* Anim = nullptr;
    };

} // namespace basilisk
