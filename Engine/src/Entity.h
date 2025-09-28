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
        Entity();
        virtual ~Entity();
        
#pragma region Abstracts
        /// <summary>
        /// Initializes the entity. Should be called inside an implemented Init call from base game.
        /// </summary>
        virtual void Init() = 0;

        /// <summary>
        /// Updates the entity. Should be called inside an implemented Update call from base game.
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// Draws the entity. Should be called inside an implemented Draw call from base game.
        /// </summary>
        virtual void Draw() = 0;
        
#pragma endregion

#pragma region Setters
        /// <summary>
        /// Sets and rotates an entity.
        /// </summary>
        /// <param name="angle">Angle to rotate the entity, counterclockwise</param>
        /// <param name="rotationAxis">Axis to which rotate</param> 
        void SetRotation(float angle, Axis rotationAxis);

        /// <summary>
        /// Sets scale vector and scales accordingly.
        /// </summary>
        /// <param name="scaling">Saling Vector</param>
        void SetScaling(const glm::vec3& scaling);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="scale">Size </param>
        /// <param name="scalingAxis"></param>
        void SetScaling(float scale, Axis scalingAxis);
        void SetPosition(const glm::vec3& newPosition);
        
        void SetMaterial(const std::shared_ptr<Material>& material);

#pragma endregion

#pragma region Getters
        [[nodiscard]] virtual glm::vec3 GetPosition() const;
        [[nodiscard]] virtual glm::vec3 GetScale() const;
        [[nodiscard]] virtual glm::vec3 GetRotation() const;

        [[nodiscard]] std::shared_ptr<Material> GetMaterial() const;
        [[nodiscard]] glm::mat4 GetModelMatrix() const;
        
#pragma endregion
        
        bool IsActive = true;

    protected:
        void UpdateBuffers() const;
        
        void FillVertices(float vertices[], int amountVertices);
        void FillIndices(unsigned int indices[], int amountIndices);
        
        glm::mat4 ModelMatrix = glm::mat4(1.0f);

        glm::mat4 TranslateMatrix = glm::mat4(1.0f);
        glm::mat4 ScaleMatrix = glm::mat4(1.0f);
        glm::mat4 RotationMatrix = glm::mat4(1.0f);
    

        
    private:
        std::shared_ptr<Material> Mat = nullptr;

        float* Vertices = nullptr;
        unsigned int* Indices = nullptr;
        int AmountVertices = 0;
        int AmountIndices = 0;

        void UpdateRotationMatrix();
        void UpdateTranslateMatrix();
        
        void UpdateModelMatrix();

        glm::vec3 Position = {0, 0, 0};
        glm::vec3 Scaling = {1, 1, 1};
        glm::vec3 Rotation = {0, 0, 0};
    };
} // basilisk 
