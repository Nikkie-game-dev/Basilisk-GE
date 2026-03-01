#include "Tile.h"

namespace basilisk
{
    Tile::Tile(const Frame& frame, const short col, const short row) : 
        Col(col), Row(row), HasCollision(false)
    {
        float vertices[] = {
            //@formatter:off
            // positions            // colors                    // texture coords
            0.5f,  0.5f,  0.0f,      1.0f, 1.0f, 1.0f, 1.0f,     frame.TopRight.x,    frame.TopRight.y,
            0.5f,  -0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,     frame.BottomRight.x, frame.BottomRight.y,
            -0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,     frame.BottomLeft.x,  frame.BottomLeft.y,
            -0.5f, 0.5f,  0.0f,      1.0f, 1.0f, 1.0f, 1.0f,     frame.TopLeft.x,     frame.TopLeft.y
            //@formatter:on
        };

        unsigned int indices[]{
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };

        this->FillVertices(vertices, sizeof(vertices));
        this->FillIndices(indices, sizeof(indices));
    }

    void Tile::Update()
    {
    }

    void Tile::Draw()
    {
        Entity2D::Draw();
    }

} // namespace basilisk
