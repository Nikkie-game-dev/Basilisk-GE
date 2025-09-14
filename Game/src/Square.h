#pragma once
#include "Entity2D.h"

namespace game
{
    class Square final : public basilisk::Entity2D
    {
    public:
        Square(glm::vec2 topLeftPos, glm::vec2 size);
        ~Square();
        void Init() override;
        void Update() override;
        glm::vec2 Position;
        glm::vec2 Size;

    private:
        int vertexCount = 12;
        int indexCount = 6;
        float* vertices;
        unsigned int* indices;

    };
} // namespace game
