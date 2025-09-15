#include "Square.h"

#include "Renderer.h"

namespace basilisk
{

    Square::Square(glm::vec2 topLeftPos, glm::vec2 size, bool isSolidColor, basilisk::Color color = basilisk::Color(0, 0, 0)) :
        Shape(isSolidColor, color)
    {
        auto topRight = glm::vec2(topLeftPos.x + size.x, topLeftPos.y);
        auto bottomLeft = glm::vec2(topLeftPos.x, topLeftPos.y - size.y);
        auto bottomRight = glm::vec2(topLeftPos.x + size.x, topLeftPos.y - size.y);

        if (isSolidColor)
        {
            SetVerticesSolid(topLeftPos, topRight, bottomLeft, bottomRight);
        }
        else
        {
            SetVertices(topLeftPos, topRight, bottomLeft, bottomRight);
        }

        unsigned int indices[]{
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };

        FillIndices(indices, sizeof(indices));

        this->Scaling = glm::vec3(size.x, size.y, 1.0f);
        this->Position = glm::vec3(topLeftPos.x, topLeftPos.y, 0.0f);

        UpdateBuffers();
    }

    void Square::SetVerticesSolid(const glm::vec2 topLeftPos, const glm::vec2 topRight, const glm::vec2 bottomLeft, const glm::vec2 bottomRight)
    {
        float vertices[]{
            topRight.x, topRight.y, 0.0f, // top right
            bottomRight.x, bottomRight.y, 0.0f, // bottom right
            bottomLeft.x, bottomLeft.y, 0.0f, // bottom left
            topLeftPos.x, topLeftPos.y, 0.0f // top left
        };

        FillVertices(vertices, sizeof(vertices));

    }
    void Square::SetVertices(const glm::vec2 topLeftPos, const glm::vec2 topRight, const glm::vec2 bottomLeft, const glm::vec2 bottomRight)
    {
        float vertices[]{
            topRight.x, topRight.y, 0.0f,        1.0f, 0.0f, 0.0f, 1.0f,  // top right
            bottomRight.x, bottomRight.y,0.0f,   0.0f, 1.0f, 0.0f, 1.0f,  // bottom right
            bottomLeft.x, bottomLeft.y, 0.0f,    0.0f, 0.0f, 1.0f, 1.0f,  // bottom left
            topLeftPos.x, topLeftPos.y, 0.0f,    1.0f, 1.0f, 1.0f, 0.0f   // top left
        };

        FillVertices(vertices, sizeof(vertices));
    }

    void Square::Init()
    {
        Mat.BuildShader();
    }
    void Square::Update()
    {
        SetPosition({-0.6f, -0.4f});
        SetScaling({0.2f, 0.2f});
        SetRotation(-20.0f);
    }
    void Square::Draw()
    {
        if (this->Mat.GetIsSolid())
        {
            Renderer::GetInstance().Draw(Mat.GetShaderProgram(), this->Color);
        }
        else
        {
            Renderer::GetInstance().Draw(Mat.GetShaderProgram());

        }
    }
}
