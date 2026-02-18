#include "Entity2D.h"

#include "Entity.h"
#include "Renderer.h"

namespace basilisk
{
    float Entity2D::GetRotation2D(const bool isRads) const
    {
        return GetRotation(isRads).z;
    }

    glm::vec2 Entity2D::GetScale2D() const
    {
        return GetScale();
    }

    glm::vec2 Entity2D::GetPosition2D() const
    {
        return GetPosition();
    }

    void Entity2D::SetRotation(const float& angle, const bool isRads)
    {
        this->Entity::SetRotation(angle, Axis::Z, isRads);
    }

    void Entity2D::SetScaling(const glm::vec2& scaling)
    {
        this->Entity::SetScaling({scaling.x, scaling.y, 1.0f});
    }

    void Entity2D::SetPosition(const glm::vec2& newPosition)
    {
        this->Entity::SetPosition({newPosition.x, newPosition.y, 0.0f});
    }
    
    void Entity2D::Init()
    {
        const auto mat = this->GetMaterial();
        this->UpdateBuffers();

        mat->BuildShader();

        if (!mat->IsProjectionSent)
        {
            Renderer::GetInstance().LoadProjectionMatrix();
            mat->UpdateGLMatrix(Renderer::GetInstance().GetProjectionMatrix(), "projection");
            mat->IsProjectionSent = true;
        }
    }

    void Entity2D::Draw()
    {
        const auto mat = this->GetMaterial();
        auto& renderer = Renderer::GetInstance();

        renderer.UpdateViewMatrix();
        const auto matrix = renderer.GetProjectionMatrix() * renderer.GetViewMatrix() * this->ModelMatrix;
        mat->UpdateGLMatrix(matrix, "matrix");
        
        renderer.Draw(mat->GetShaderProgram(), buffers.Vao, buffers.AmountIndices);

    }

    glm::vec3 Entity2D::GetPosition() const
    {
        return Entity::GetPosition();
    }

    glm::vec3 Entity2D::GetScale() const
    {
        return Entity::GetScale();
    }

    glm::vec3 Entity2D::GetRotation(const bool isRads) const
    {
        return Entity::GetRotation(isRads);
    }

} // namespace basilisk
