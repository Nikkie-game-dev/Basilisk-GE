#include "Tile.h"

namespace basilisk
{
    Tile::Tile(const basilisk::Frame& frame, const short col, const short row) :
        Shape(false),
        HasCollision(false), Col(col), Row(row), Frame(frame)
    {

    }

    void Tile::Update()
    {
    }

    void Tile::SetVertices()
    {
        float vertices[] = {
            //@formatter:off
            // positions            // colors                    // texture coords
            0.5f,  0.5f,  0.0f,      1.0f, 1.0f, 1.0f, 1.0f,     this->Frame.TopRight.x,    this->Frame.TopRight.y,
            0.5f,  -0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,     this->Frame.BottomRight.x, this->Frame.BottomRight.y,
            -0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,     this->Frame.BottomLeft.x,  this->Frame.BottomLeft.y,
            -0.5f, 0.5f,  0.0f,      1.0f, 1.0f, 1.0f, 1.0f,     this->Frame.TopLeft.x,     this->Frame.TopLeft.y
            //@formatter:on
        };
        this->FillVertices(vertices, sizeof(vertices));
    }

    void Tile::SetIndices()
    {
        unsigned int indices[]{
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };

        this->FillIndices(indices, sizeof(indices));
    }

} // namespace basilisk
