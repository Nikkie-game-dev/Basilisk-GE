#pragma once
#include <glm/glm.hpp>

#include "Entity.h"

namespace basilisk
{
    enum class Axis: char
    {
        X,
        Y,
    };

    class BASILISK_API Entity2D : Entity
    {
    public:
        void Rotate(float angle);
        void Scale(float scale, Axis scalingAxis);

        // Getters:
        
        [[nodiscard]] glm::vec2 GetRotation() const
        {
            return Rotation;
        }

        [[nodiscard]] glm::vec2 GetScale() const
        {
            return Scaling;
        }

        glm::vec2 Position = {0, 0};

    private:
        glm::vec2 Scaling = {1, 1};
        glm::vec2 Rotation = {0,0};
    };
} // basilisk 
