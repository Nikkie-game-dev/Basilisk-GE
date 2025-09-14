#include "Square.h"

namespace game
{
    Square::Square(glm::vec2 topLeftPos, glm::vec2 size)
    {
        auto topRight = glm::vec2(topLeftPos.x + size.x, topLeftPos.y);
        auto bottomLeft = glm::vec2(topLeftPos.x, topLeftPos.y - size.y);
        auto bottomRight = glm::vec2(topLeftPos.x + size.x, topLeftPos.y - size.y);

        vertexCount = 12;
        indexCount = 6;

        vertices = new float[vertexCount]{
            topRight.x, topRight.y, 0.0f, // top right
            bottomRight.x,  bottomRight.y, 0.0f, // bottom right
            bottomLeft.x, bottomLeft.y, 0.0f, // bottom left
            topLeftPos.x, topLeftPos.y,  0.0f // top left
        };

        indices = new unsigned int[indexCount]{
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };

        FillVertices(vertices, vertexCount);
        FillIndices(indices, indexCount);

        this->Size = size;
        this->Position = topLeftPos;

        UpdateBuffers();
    }

    Square::~Square()
    {
        delete[] vertices;
        delete[] indices;
    }

    void Square::Init()
    {
        UpdateBuffers();
    }

    void Square::Update()
    {
        SetPosition({0.6f, -0.4f});
        SetScaling({1.2f, 1.2f});
        SetRotation(-20.0f);

        Entity2D::Update();
    }
}
