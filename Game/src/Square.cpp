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
        SetPosition({-0.3f, 0.5f});
        SetScaling({1.0f, 1.0f});
        SetRotation(0.0f);

        Entity2D::Update();
    }

    void Square::SetRotation(float rotation)
    {
        basilisk::Entity2D::SetRotation(rotation);

    }
    void Square::SetScaling(glm::vec2 scaling)
    {
        basilisk::Entity2D::SetScaling(scaling);
    }
    void Square::SetScaling(float scale, basilisk::Axis scalingAxis)
    {
        basilisk::Entity2D::SetScaling(scale, scalingAxis);
    }
    void Square::SetPosition(glm::vec2 newPosition)
    {
        basilisk::Entity2D::SetPosition(newPosition);
    }

    
}
