#include "Tile.h"

#include "Renderer.h"

namespace basilisk
{
    Tile::Tile(Frame frame,
               short col,
               short row,
               const std::string& textureFilePath,
               glm::vec2 size,
               glm::vec2 textureSize,
               Filters filter,
               FitMode fitMode) :
        Sprite(textureFilePath,
               {static_cast<float>(col) * size.x + size.x / 2, textureSize.y - static_cast<float>(row) * size.y + size.y / 2},
               size,
               filter,
               fitMode),
        Col(col), Row(row)
    {

        constexpr int start = 7;
        constexpr int stride = 9;

        this->buffers.Vertices[start] = frame.TopRight.x;
        this->buffers.Vertices[start + 1] = frame.TopRight.y;
        this->buffers.Vertices[start + stride] = frame.BottomRight.x;
        this->buffers.Vertices[start + stride + 1] = frame.BottomRight.y;
        this->buffers.Vertices[start + stride * 2] = frame.BottomLeft.x;
        this->buffers.Vertices[start + stride * 2 + 1] = frame.BottomLeft.y;
        this->buffers.Vertices[start + stride * 3] = frame.TopLeft.x;
        this->buffers.Vertices[start + stride * 3 + 1] = frame.TopLeft.y;

        Renderer::GetInstance().BindBufferData(buffers.Vbo, buffers.AmountVertices, buffers.Vertices, start, 2);
    }
} //namespace basilisk
