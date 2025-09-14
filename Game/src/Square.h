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
        void SetRotation(float rotation);
        void SetScaling(glm::vec2 scaling);
        void SetScaling(float scale, basilisk::Axis scalingAxis);
        void SetPosition(glm::vec2 newPosition);
        
        glm::vec2 Position;
        glm::vec2 Size;

    private:
        int vertexCount = 12;
        int indexCount = 6;
        float* vertices;
        unsigned int* indices;

    };
} // namespace game
