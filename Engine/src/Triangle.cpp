#include "Triangle.h"

#include <array>

#include "Renderer.h"

namespace basilisk
{

    Triangle::Triangle(const glm::vec2& center, const glm::vec2& size, const bool& isSolid, const basilisk::Color& color) :
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
        constexpr int amountVert = 3;
        constexpr int amountDim = 3;

        std::array<float, amountVert * (amountDim + Color::ColorParamsAmount)> vertices;

        if (!this->IsSolid)
        {
            //@formatter:off
            vertices = 
            {
                0.0f,  0.5f,  0.0f,    1.0f, 0.0f, 0.0f, 1.0f,  // top right
                0.5f,  -0.5f, 0.0f,    0.0f, 1.0f, 0.0f, 1.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f, 1.0f,  // bottom left
            };
            //@formatter:on
        }
        else
        {
            const auto color = Color::Normalize(this->Color);
            //@formatter:off
            vertices = 
            {
                 0.0f,  0.5f, 0.0f,   color.R, color.G, color.B, color.A, // top right
                 0.5f, -0.5f, 0.0f,   color.R, color.G, color.B, color.A, // bottom right
                -0.5f, -0.5f, 0.0f,   color.R, color.G, color.B, color.A, // bottom left
            };
            //@formatter:on
        }

        this->FillVertices(vertices.data(), sizeof(vertices));

    }
}
