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


    void Sprite::UpdateAnimation(float delta)
    {
        if (!this->Animation)
            return;

        this->Animation->Update(delta);

        UpdateCurrentFrame();
    }

    void Sprite::UpdateCurrentFrame()
    {
        Animation::Frame current = this->Animation->GetCurrentFrame();

        float vertices[] = 
        {
            // positions            // colors                    // texture coords
            0.5f,  0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      current.topRightUV.x,    current.topRightUV.y, // top right
            0.5f,  -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      current.bottomRightUV.x, current.bottomRightUV.y, // bottom right
            -0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      current.bottomLeftUV.x,  current.bottomLeftUV.y, // bottom left
            -0.5f, 0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      current.topLeftUV.x,     current.topLeftUV.y // top left
        };

        this->FillVertices(vertices, sizeof(vertices));
    }
}
