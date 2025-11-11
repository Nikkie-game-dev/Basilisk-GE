#pragma once
#include "Animation.h"
#include "Entity2D.h"

namespace basilisk
{
    class BASILISK_API Sprite : public Entity2D
    {
    public:
        Sprite(const std::string& textureDir, glm::vec2 center, glm::vec2 size);
        
        void Init() override;
        void Draw() override;
        void SetAnimation(Animation* animation);
        
        /// <summary>
        /// Updates the animation
        /// </summary>
        /// <param name="delta"></param>
        void UpdateAnimation(float delta);

    private:
        void UpdateCurrentFrame() const;
        unsigned int Texture;
        Animation* Animation = nullptr;
    };

} // namespace basilisk
