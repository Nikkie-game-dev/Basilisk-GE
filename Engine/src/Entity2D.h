#pragma once
#include "glm/glm.hpp"

#include "Entity.h"

namespace basilisk
{
    enum class Axis: char
    {
        X,
        Y,
    };

    class BASILISK_API Entity2D : public Entity
    {
    public:
        virtual ~Entity2D() = default;

        [[nodiscard]] glm::vec2 GetRotation() const;
        [[nodiscard]] glm::vec2 GetScale() const;
        [[nodiscard]] glm::vec2 GetPosition() const;

        void SetRotation(float angle);
        void SetRotation(glm::vec2 rotation);
        void SetScaling(glm::vec2 scaling);
        void SetScaling(float scale, Axis scalingAxis);
        void SetPosition(glm::vec2 newPosition);
        
    private:
        glm::vec2 Position = {0, 0};
        glm::vec2 Scaling = {1, 1};
        glm::vec2 Rotation = {0,0};
    };
} // basilisk 
