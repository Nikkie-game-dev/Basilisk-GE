#include "Triangle.h"

#include "Renderer.h"

namespace basilisk
{

    Triangle::Triangle(const glm::vec2 center, const glm::vec2 size, const bool isSolid, const basilisk::Color& color) :
        Shape(color, isSolid)
    {
        Triangle::CalculateVertices(center, size);
        Triangle::SetVertices();

        unsigned int indices[]{
            0, 1, 2, // first triangle
        };

        this->FillIndices(indices, sizeof(indices));

        Triangle::SetPosition(center);
    }

    void Triangle::CalculateVertices(const glm::vec2 center, const glm::vec2 size)
    {
        this->Top = glm::vec2(center.x, center.y  + size.y / 2);
        this->BottomRight = glm::vec2(center.x + size.x / 2, center.y - size.y / 2);
        this->BottomLeft = glm::vec2(center.x - size.x / 2, center.y - size.y / 2);
    }
    
    void Triangle::SetVertices()
    {
        if (!this->IsSolid)
        {
            //@formatter:off
            float vertices[]{
                this->Top.x,         this->Top.y,         0.0f,        1.0f, 0.0f, 0.0f, 1.0f,  // top right
                this->BottomRight.x, this->BottomRight.y, 0.0f,        0.0f, 1.0f, 0.0f, 1.0f,  // bottom right
                this->BottomLeft.x,  this->BottomLeft.y,  0.0f,        0.0f, 0.0f, 1.0f, 1.0f,  // bottom left
            };
            //@formatter:on
            this->FillVertices(vertices, sizeof(vertices));
        }
        else
        {
            //@formatter:off
            float vertices[]{
                this->Top.x,         this->Top.y,         0.0f,  // top right
                this->BottomRight.x, this->BottomRight.y, 0.0f,  // bottom right
                this->BottomLeft.x,  this->BottomLeft.y,  0.0f,  // bottom left
            };
            //@formatter:on
            this->FillVertices(vertices, sizeof(vertices));
        }
    }
}
