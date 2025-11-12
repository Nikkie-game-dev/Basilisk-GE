#pragma once
#include "Animation.h"
#include "Entity2D.h"
#include "TextureImporter.h"

namespace basilisk
{
    class BASILISK_API Sprite : public Entity2D
    {
    public:
        Sprite(const std::string& textureDir, const glm::vec2 center, const glm::vec2 size, 
               const Filters filter = Filters::NEAREST, const FitMode fitMode = FitMode::REPEAT);
        
        void Init() override;
        void Draw() override;
        void SetAnimation(Animation* animation);
        
        /// <summary>
        /// Updates the animation
        /// </summary>
        /// <param name="delta"></param>
        void UpdateAnimation(float delta);
        void ChangeAnimation(Animation* newAnimation);

        bool FlipSpriteX = false;
        bool FlipSpriteY = false;
       
    private:
        void UpdateCurrentFrame() const;
        void FlipSprite(glm::vec2& topRightUV, glm::vec2& topLeftUV, glm::vec2& bottomLeftUV, glm::vec2& bottomRightUV) const;
        unsigned int Texture;
        Animation* Animation = nullptr;
    };

} // namespace basilisk
