#include "Square.h"

#include "Entity.h"
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
        if (!this->IsSolid)
        {
            //@formatter:off
            float vertices[]
            {
                 0.5f,  0.5f, 0.0f,       1.0f, 0.0f, 0.0f, 1.0f, // top right
                 0.5f, -0.5f, 0.0f,       0.0f, 1.0f, 0.0f, 1.0f, // bottom right
                -0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f, 1.0f, // bottom left
                -0.5f,  0.5f, 0.0f,       1.0f, 1.0f, 1.0f, 0.0f // top left
            };
            //@formatter:on
            this->FillVertices(vertices, sizeof(vertices));
        }
        else
        {
            //@formatter:off
            float vertices[]
            {
                 0.5f,  0.5f, 0.0f, // top right
                 0.5f, -0.5f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f, // bottom left
                -0.5f,  0.5f, 0.0f // top left
            };
            //@formatter:on
            this->FillVertices(vertices, sizeof(vertices));
        }
    }

} // namespace basilisk
