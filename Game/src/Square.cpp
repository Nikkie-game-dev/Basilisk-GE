#include "Square.h"

namespace game
{
    Square::Square(glm::vec2 topLeftPos, glm::vec2 size)
    {
        auto topRight = glm::vec2(topLeftPos.x + size.x, topLeftPos.y);
        auto bottomLeft = glm::vec2(topLeftPos.x, topLeftPos.y - size.y);
        auto bottomRight = glm::vec2(topLeftPos.x + size.x, topLeftPos.y - size.y);

        indexCount = 6;

        float vertices[] {
            topRight.x, topRight.y, 0.0f, // top right
            bottomRight.x,  bottomRight.y, 0.0f, // bottom right
            bottomLeft.x, bottomLeft.y, 0.0f, // bottom left
            topLeftPos.x, topLeftPos.y,  0.0f // top left
        };

        unsigned int indices[]{
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };

        FillVertices(vertices, sizeof(vertices));
        FillIndices(indices, sizeof(indices));

        this->Size = size;
        this->Position = topLeftPos;

        UpdateBuffers();
    }

    void Square::Init()
    {
        UpdateBuffers();
    }

    void Square::Update()
    {
        SetPosition({-0.6f, -0.4f});
        SetScaling({0.2f, 0.2f});
        SetRotation(-20.0f);

        Entity2D::Update();
    }
}
