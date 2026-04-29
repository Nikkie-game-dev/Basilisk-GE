#include "Cube.h"

namespace basilisk
{

    Cube::Cube(bool isSolid, const vec3& center, const vec3& size, const basilisk::Color& color) :
        Shape3D(isSolid, center, size, color)
    {
        Cube::SetIndices();
        Cube::SetVertices();
    }

    void Cube::SetVertices()
    {
        constexpr int amountVert = 8;

        std::array<float, amountVert * (AMOUND_DIM + Color::ColorParamsAmount)> vertices;

        if (!this->IsSolid)
        {
            //@formatter:off
            vertices = 
            {
                0.5f,  0.5f, 0.0f,       1.0f, 0.0f, 0.0f, 1.0f, // front top right
                0.5f, -0.5f, 0.0f,       0.0f, 1.0f, 0.0f, 1.0f, // front bottom right
               -0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f, 1.0f, // front bottom left
               -0.5f,  0.5f, 0.0f,       1.0f, 1.0f, 1.0f, 0.0f, // front top left
                
                0.5f,  0.5f, -0.5f,      1.0f, 0.0f, 0.0f, 1.0f, // back top right
                0.5f, -0.5f, -0.5f,      0.0f, 1.0f, 0.0f, 1.0f, // back bottom right
               -0.5f, -0.5f, -0.5f,      0.0f, 0.0f, 1.0f, 1.0f, // back bottom left
               -0.5f,  0.5f, -0.5f,      1.0f, 1.0f, 1.0f, 0.0f  // back top left
           };
            //@formatter:on
        }
        else
        {

            const auto color = Color::Normalize(this->Color);
            //@formatter:off
            vertices =
            {
                0.5f,  0.5f, 0.0f,       color.R, color.G, color.B, color.A, // front top right
                0.5f, -0.5f, 0.0f,       color.R, color.G, color.B, color.A, // front bottom right
               -0.5f, -0.5f, 0.0f,       color.R, color.G, color.B, color.A, // front bottom left
               -0.5f,  0.5f, 0.0f,       color.R, color.G, color.B, color.A, // front top left
                
                0.5f,  0.5f, -0.5f,      color.R, color.G, color.B, color.A, // back top right
                0.5f, -0.5f, -0.5f,      color.R, color.G, color.B, color.A, // back bottom right
               -0.5f, -0.5f, -0.5f,      color.R, color.G, color.B, color.A, // back bottom left
               -0.5f,  0.5f, -0.5f,      color.R, color.G, color.B, color.A, // back top left
           };
            //@formatter:on
        }

        this->FillVertices(vertices.data(), sizeof(vertices));
    }

    void Cube::SetIndices()
    {
        unsigned int indices[]
        {
            //front
            0, 1, 3, // first triangle
            1, 2, 3, // second triangle

            //back
            4, 5, 7, // first triangle
            5, 6, 7, // second triangle

            //left
            3, 7, 6,
            6, 2, 3,

            //right
            0, 3, 4,
            5, 1, 6,

            //top
            3, 7, 4,
            3, 4, 0,

            //bottom
            1, 2, 6,
            1, 5, 6,
        };

        this->FillIndices(indices, sizeof(indices));
    }
}
