#pragma once
#include "Animation.h"
#include "Entity2D.h"
#include "TextureImporter.h"

namespace basilisk
{
    /// <summary>
    /// A 2D sprite. It's a textured entity that can have animations.
    /// </summary>
    class BASILISK_API Sprite : public Entity2D
    {
    public:
        /// <summary>
        /// The Sprite constructor.
        /// </summary>
        /// <param name="textureDir">Directory to the texture</param>
        /// <param name="center">The position of the sprite at the center</param>
        /// <param name="size">The size of the sprite in pixels</param>
        /// <param name="filter">A filter for texture rendering</param>
        /// <param name="fitMode">The fit mode. It tells the texture how it should fit in the size limits</param>
        Sprite(const std::string& textureDir,
               const glm::vec2& center,
               const glm::vec2& size,
               Filters filter = Filters::NEAREST,
               FitMode fitMode = FitMode::REPEAT);
        
        void Draw() override;

        /// <summary>
        /// Sets the animation for the sprite.
        /// </summary>
        /// <param name="animation"></param>
        void SetAnimation(Animation* animation);
        
        /// <summary>
        /// Updates the animation
        /// </summary>
        /// <param name="delta"></param>
        void UpdateAnimation(const float delta);

        /// <summary>
        /// Transitions into a new animation
        /// </summary>
        /// <param name="newAnimation"></param>
        void ChangeAnimation(Animation* newAnimation);

        /// <summary>
        /// Flips the sprite horizontally
        /// </summary>
        bool FlipSpriteX = false;
        /// <summary>
        /// Flips the sprite vertically
        /// </summary>
        bool FlipSpriteY = false;
       
    private:
        void UpdateCurrentFrame() const;
        void FlipSprite(glm::vec2& topRightUV, glm::vec2& topLeftUV, glm::vec2& bottomLeftUV, glm::vec2& bottomRightUV) const;
        
        unsigned int Texture;
        Animation* Animation = nullptr;
    };

} // namespace basilisk
