#include "Sprite.h"

#include "Renderer.h"
#include "TextureImporter.h"

namespace basilisk
{
    Sprite::Sprite(const std::string& textureDir, const glm::vec2& center, const glm::vec2& size, 
                   const Filters filter, const FitMode fitMode)
    {
        this->Entity2D::SetPosition(center);
        this->Entity2D::SetScaling(size);

        this->Texture = TextureImporter::MakeTextureData(textureDir, filter, fitMode).textureID;

        float vertices[] = 
        {
            //@formatter:off
            // positions            // colors                    // texture coords
            0.5f,   0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      1.0f, 1.0f, // top right
            0.5f,  -0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      1.0f, 0.0f, // bottom right
            -0.5f, -0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      0.0f, 0.0f, // bottom left
            -0.5f,  0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      0.0f, 1.0f // top left
            //@formatter:on
        };

        unsigned int indices[]
        {
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };

        this->FillVertices(vertices, sizeof(vertices));
        this->FillIndices(indices, sizeof(indices));
    }

    void Sprite::Draw()
    {
        TextureImporter::BindTexture(this->Texture);
        Entity2D::Draw();
        TextureImporter::UnbindTexture();
    }


    void Sprite::SetAnimation(basilisk::Animation* animation)
    {
        this->Animation = animation;
    }


    void Sprite::UpdateAnimation(const float& delta)
    {
        if (!this->Animation)
            return;

        bool hasChanged;

        this->Animation->Update(delta, hasChanged);

        if (hasChanged)
        {
            this->UpdateCurrentFrame();
        }
    }

    void Sprite::ChangeAnimation(basilisk::Animation* newAnimation)
    {
        if (this->Animation->GetId() != newAnimation->GetId())
        {
            this->Animation->Stop();
            this->SetAnimation(newAnimation);
            this->Animation->Play();
            this->UpdateCurrentFrame();
        }
    }

    void Sprite::UpdateCurrentFrame() const
    {
        constexpr int start = 7;
        constexpr int amountVerticesPerCorner = 9;

        auto [topLeftUV, topRightUV, bottomLeftUV, bottomRightUV] = this->Animation->GetCurrentFrame();

        FlipSprite(topRightUV, topLeftUV, bottomLeftUV, bottomRightUV);

        this->buffers.Vertices[start] = topRightUV.x;
        this->buffers.Vertices[start + 1] = topRightUV.y;
        this->buffers.Vertices[start + amountVerticesPerCorner] = bottomRightUV.x;
        this->buffers.Vertices[start + amountVerticesPerCorner + 1] = bottomRightUV.y;
        this->buffers.Vertices[start + amountVerticesPerCorner * 2] = bottomLeftUV.x;
        this->buffers.Vertices[start + amountVerticesPerCorner * 2 + 1] = bottomLeftUV.y;
        this->buffers.Vertices[start + amountVerticesPerCorner * 3] = topLeftUV.x;
        this->buffers.Vertices[start + amountVerticesPerCorner * 3 + 1] = topLeftUV.y;

        Renderer::GetInstance().BindBufferData(buffers.Vbo, buffers.AmountVertices, buffers.Vertices, start, 2);
    }

    void Sprite::FlipSprite(glm::vec2& topRightUV, glm::vec2& topLeftUV, glm::vec2& bottomLeftUV, glm::vec2& bottomRightUV) const
    {
        if (!this->FlipSpriteX && !this->FlipSpriteY)
            return;

        glm::vec2 topLeftUVFlipped = {this->FlipSpriteX ? topRightUV.x : topLeftUV.x, 
                                      this->FlipSpriteY ? bottomLeftUV.y : topLeftUV.y};

        glm::vec2 topRightUVFlipped = {this->FlipSpriteX ? topLeftUV.x : topRightUV.x, 
                                       this->FlipSpriteY ? bottomRightUV.y : topRightUV.y};

        glm::vec2 bottomLeftUVFlipped = {this->FlipSpriteX ? bottomRightUV.x : bottomLeftUV.x,
                                         this->FlipSpriteY ? topLeftUV.y : bottomLeftUV.y};

        glm::vec2 bottomRightUVFlipped = {this->FlipSpriteX ? bottomLeftUV.x : bottomRightUV.x,
                                          this->FlipSpriteY ? topRightUV.y : bottomRightUV.y};

        topLeftUV = topLeftUVFlipped;
        topRightUV = topRightUVFlipped;
        bottomLeftUV = bottomLeftUVFlipped;
        bottomRightUV = bottomRightUVFlipped;
    }
} // namespace basilisk
