#include "Square.h"

#include <array>
#include "Entity.h"
#include "Renderer.h"

namespace basilisk
{

    Square::Square(const glm::vec2 center,
                   const glm::vec2 size,
                   const bool isSolidColor,
                   const basilisk::Color color = basilisk::Color(0, 0, 0)) :
        Shape(color, isSolidColor)
    {
        this->Entity2D::SetPosition(center);
        this->Entity2D::SetScaling(size);

        Square::SetVertices();

        unsigned int indices[]
        {
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };

        this->FillIndices(indices, sizeof(indices));
    }


    void Square::SetVertices()
    {
        constexpr int amountVert = 4;
        constexpr int amountDim = 3;
        std::array<float, amountVert * (amountDim + Color::ColorParamsAmount)> vertices;

        if (!this->IsSolid)
        {
            //@formatter:off
            vertices = 
            {
                 0.5f,  0.5f, 0.0f,       1.0f, 0.0f, 0.0f, 1.0f, // top right
                 0.5f, -0.5f, 0.0f,       0.0f, 1.0f, 0.0f, 1.0f, // bottom right
                -0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f, 1.0f, // bottom left
                -0.5f,  0.5f, 0.0f,       1.0f, 1.0f, 1.0f, 0.0f // top left
            };
            //@formatter:on
        }
        else
        {

            const auto color = Color::Normalize(this->Color);
            //@formatter:off
            vertices =
            {
                 0.5f,  0.5f, 0.0f,       color.R, color.G, color.B, color.A, // top right
                 0.5f, -0.5f, 0.0f,       color.R, color.G, color.B, color.A, // bottom right
                -0.5f, -0.5f, 0.0f,       color.R, color.G, color.B, color.A, // bottom left
                -0.5f,  0.5f, 0.0f,       color.R, color.G, color.B, color.A  // top left
            };
            //@formatter:on
        }
        
        this->FillVertices(vertices.data(), sizeof(vertices));
    }

} // namespace basilisk
