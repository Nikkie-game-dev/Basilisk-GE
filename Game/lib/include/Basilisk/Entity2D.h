#pragma once
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

        [[nodiscard]] float GetRotation() const;
        [[nodiscard]] glm::vec2 GetScale() const;
        [[nodiscard]] glm::vec2 GetPosition() const;

        virtual void SetRotation(float angle);
        virtual void SetScaling(glm::vec2 scaling);
        virtual void SetScaling(float scale, Axis scalingAxis);
        virtual void SetPosition(glm::vec2 newPosition);
        virtual void Update() override;
        
    private:
        glm::vec2 Position = {0, 0};
        glm::vec2 Scaling = {1, 1};
        float Rotation = 0.0f;
        glm::mat4 ModelMatrix = glm::mat4(1.0f);
        glm::mat4 TranslateMatrix = glm::mat4(1.0f);
        glm::mat4 ScaleMatrix = glm::mat4(1.0f);
        glm::mat4 RotationMatrix = glm::mat4(1.0f);
        void UpdateRotationMatrix();
        void UpdateTranslateMatrix();
        void UpdateModelMatrix();
    };
} // basilisk 
