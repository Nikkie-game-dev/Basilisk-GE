#include "Triangle.h"

#include "Renderer.h"

namespace basilisk
{

    Triangle::Triangle(const glm::vec2 center, const glm::vec2 size, const bool isSolid, const basilisk::Color& color) :
        Shape(color, isSolid)
    {
        this->Entity2D::SetPosition(center);
        this->Entity2D::SetScaling(size);

        Triangle::SetVertices();

        unsigned int indices[]
        {
            0, 1, 2, // triangle
        };

        this->FillIndices(indices, sizeof(indices));
    }

    void Triangle::SetVertices()
    {
        if (!this->IsSolid)
        {
            //@formatter:off
            float vertices[]
            {
                0.0f,  0.5f,  0.0f,        1.0f, 0.0f, 0.0f, 1.0f,  // top right
                0.5f,  -0.5f, 0.0f,        0.0f, 1.0f, 0.0f, 1.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,        0.0f, 0.0f, 1.0f, 1.0f,  // bottom left
            };
            //@formatter:on
            this->FillVertices(vertices, sizeof(vertices));
        }
        else
        {
            //@formatter:off
            float vertices[]
            {
                0.0f,  0.5f,  0.0f,  // top right
                0.5f,  -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
            };
            //@formatter:on
            this->FillVertices(vertices, sizeof(vertices));
        }
    }
}
