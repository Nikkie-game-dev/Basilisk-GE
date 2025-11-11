#include "Sprite.h"

#include "Renderer.h"
#include "TextureImporter.h"

namespace basilisk
{
    Sprite::Sprite(const std::string& textureDir, const glm::vec2 center, const glm::vec2 size)
    {
        this->Entity2D::SetPosition(center);
        this->Entity2D::SetScaling(size);

        this->Texture = TextureImporter::MakeTexture(textureDir);

        float vertices[] =
        {
            // positions            // colors                    // texture coords
            0.5f,   0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      1.0f, 1.0f, // top right
            0.5f,  -0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      1.0f, 0.0f, // bottom right
            -0.5f, -0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      0.0f, 0.0f, // bottom left
            -0.5f,  0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      0.0f, 1.0f // top left
        };

        unsigned int indices[]
        {
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };

        this->FillVertices(vertices, sizeof(vertices));
        this->FillIndices(indices, sizeof(indices));
    }

    Sprite::~Sprite()
    {
    }

    //Sprite::Sprite(const Sprite& other)
    //{
    //}

    //Sprite& Sprite::operator=(const Sprite& other)
    //{
    //}

    //Sprite& Sprite::operator=(Sprite&& other) noexcept
    //{
    //    return default;
    //}

    void Sprite::Init()
    {
        const auto mat = this->GetMaterial();
        this->UpdateBuffers();

        mat->BuildShader();

        if (!mat->IsProjectionSent)
        {
            Renderer::GetInstance().LoadProjectionMatrix();
            mat->UpdateGLMatrix(Renderer::GetInstance().GetProjectionMatrix(), "projection");
            mat->IsProjectionSent = true;
        }
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


    void Sprite::UpdateAnimation(const float delta)
    {
        if (!this->Animation)
            return;

        bool hasChanged;

        this->Animation->Update(delta, hasChanged);

        if (hasChanged)
        {
            UpdateCurrentFrame();
        }
    }

    void Sprite::UpdateCurrentFrame()
    {
        constexpr int start = 7;
        constexpr int amountVerticesPerCorner = 9;

        auto [topLeftUV, topRightUV, bottomLeftUV, bottomRightUV] = this->Animation->GetCurrentFrame();
        
        this->buffers.Vertices[start] = topRightUV.x;
        this->buffers.Vertices[start + 1] = topRightUV.y;
        this->buffers.Vertices[start + amountVerticesPerCorner] = bottomRightUV.x;
        this->buffers.Vertices[start + amountVerticesPerCorner + 1] = bottomRightUV.y;
        this->buffers.Vertices[start + amountVerticesPerCorner * 2] = bottomLeftUV.x;
        this->buffers.Vertices[start + amountVerticesPerCorner * 2 + 1] = bottomLeftUV.y;
        this->buffers.Vertices[start + amountVerticesPerCorner * 3] = topLeftUV.x;
        this->buffers.Vertices[start + amountVerticesPerCorner * 3 + 1] = topLeftUV.y;

        this->FillVertices(vertices, sizeof(vertices));
        Renderer::GetInstance().BindBufferData(buffers.Vbo, buffers.AmountVertices, buffers.Vertices, start, 2);
    }
}
