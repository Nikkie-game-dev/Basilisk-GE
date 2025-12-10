#include "Tile.h"

#include "Renderer.h"

namespace basilisk
{
    Tile::Tile(Frame frame,
               short col,
               short row) :
        Col(col), Row(row)
    {
        float vertices[] = 
        {
            // positions            // colors                    // texture coords
            0.5f,   0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      frame.TopRight.x, frame.TopRight.y, // top right
            0.5f,  -0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      frame.BottomRight.x, frame.BottomRight.y, // bottom right
            -0.5f, -0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      frame.BottomLeft.x, frame.BottomLeft.y, // bottom left
            -0.5f,  0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 1.0f,      frame.TopLeft.x, frame.TopLeft.y // top left
        };

        unsigned int indices[]
        {
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };

        this->FillVertices(vertices, sizeof(vertices));
        this->FillIndices(indices, sizeof(indices));
    }

    void Tile::Update()
    {
    }
    
    

} //namespace basilisk
