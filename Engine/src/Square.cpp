#include "Square.h"

#include "Renderer.h"

namespace basilisk
{

    Square::Square(const glm::vec2 center,
                   const glm::vec2 size,
                   const bool isSolidColor,
                   const basilisk::Color color = basilisk::Color(0, 0, 0)) :
        Shape(color, isSolidColor)
    {

        Square::CalculateVertices(center, size);
        Square::SetVertices();

        unsigned int indices[]{
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };

        this->FillIndices(indices, sizeof(indices));

        this->Scaling = glm::vec3(size.x, size.y, 1.0f);
        this->Position = glm::vec3(center.x, center.y, 0.0f);

    }

    void Square::SetVertices()
    {
        if (!this->IsSolid)
        {
            //@formatter:off
            float vertices[]{
                this->TopRight.x,    this->TopRight.y,    0.0f,        1.0f, 0.0f, 0.0f, 1.0f,  // top right
                this->BottomRight.x, this->BottomRight.y, 0.0f,        0.0f, 1.0f, 0.0f, 1.0f,  // bottom right
                this->BottomLeft.x,  this->BottomLeft.y,  0.0f,        0.0f, 0.0f, 1.0f, 1.0f,  // bottom left
                this->TopLeft.x,     this->TopLeft.y,     0.0f,        1.0f, 1.0f, 1.0f, 0.0f   // top left
            };
            //@formatter:on
            this->FillVertices(vertices, sizeof(vertices));
        }
        else
        {
            //@formatter:off
            float vertices[]{
                this->TopRight.x,    this->TopRight.y,    0.0f,  // top right
                this->BottomRight.x, this->BottomRight.y, 0.0f,  // bottom right
                this->BottomLeft.x,  this->BottomLeft.y,  0.0f,  // bottom left
                this->TopLeft.x,     this->TopLeft.y,     0.0f  // top left
            };
            //@formatter:on
            this->FillVertices(vertices, sizeof(vertices));

        }
    }

    void Square::Init()
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

    void Square::Draw()
    {
        Entity2D::Draw(this->Color);
    }

    void Square::CalculateVertices(const glm::vec2 center, const glm::vec2 size)
    {
        this->TopLeft = glm::vec2(center.x - size.x / 2, center.y + size.y);
        this->TopRight = glm::vec2(this->TopLeft.x + size.x, this->TopLeft.y);
        this->BottomLeft = glm::vec2(this->TopLeft.x, this->TopLeft.y - size.y);
        this->BottomRight = glm::vec2(this->TopLeft.x + size.x, this->TopLeft.y - size.y);
    }

}
