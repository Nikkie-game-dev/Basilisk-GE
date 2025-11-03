#pragma once
#include "Animation.h"
#include "Entity2D.h"

namespace basilisk
{
    class BASILISK_API Sprite : public Entity2D
    {
    public:
        Sprite(const std::string& textureDir, glm::vec2 center, glm::vec2 size);
        ~Sprite();

        //Sprite(const Sprite& other); // copy constructor
        //Sprite(Sprite&& other) noexcept; // move constructor
        //Sprite& operator=(const Sprite& other); // copy assignment
        //Sprite& operator=(Sprite&& other) noexcept; // move assignment
        //
        void Init() override;
        void SetAnimation(Animation* animation);
        /// <summary>
        /// Updates the animation
        /// </summary>
        /// <param name="delta"></param>
        void UpdateAnimation(float delta);

    private:
        void UpdateCurrentFrame();
        unsigned int Texture;
        Animation* Animation = nullptr;
    };

} // namespace basilisk
