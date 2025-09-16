#pragma once

#include "Export.h"
#include "Material.h"
#include "glm/glm.hpp"

namespace basilisk
{
    enum class Axis : char
    {
        X,
        Y,
        Z
    };


    class BASILISK_API Entity
    {
    public:
        explicit Entity(bool isSolidColor);
        virtual ~Entity();

        virtual void Init() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        
        void UpdateBuffers() const;
        void FillVertices(float vertices[], int amountVertices);
        void FillIndices(unsigned int indices[], int amountIndices);
        void SetRotation(float angle, Axis rotationAxis);
        void SetScaling(const glm::vec3& scaling);
        void SetScaling(float scale, Axis scalingAxis);
        void SetPosition(const glm::vec3& newPosition);

        bool IsActive = true;
        glm::mat4 GetModelMatrix() const;

    protected:
        glm::mat4 ModelMatrix = glm::mat4(1.0f);
        glm::vec3 Position = {0, 0, 0};
        glm::vec3 Scaling = {1, 1, 1};
        glm::vec3 Rotation = {0, 0, 0};
        glm::mat4 TranslateMatrix = glm::mat4(1.0f);
        glm::mat4 ScaleMatrix = glm::mat4(1.0f);
        glm::mat4 RotationMatrix = glm::mat4(1.0f);
        Material Mat;
        
    private:
        float* Vertices = nullptr;
        unsigned int* Indices = nullptr;
        int AmountVertices = 0;
        int AmountIndices = 0;

        void UpdateRotationMatrix();
        void UpdateTranslateMatrix();
        void UpdateModelMatrix();
    };
} // basilisk 
