#include "Entity2D.h"

#include "Renderer.h"

namespace basilisk
{
    float Entity2D::GetRotation() const
    {
        return this->Rotation.z;
    }

    glm::vec2 Entity2D::GetScale() const
    {
        return this->Scaling;
    }

    glm::vec2 Entity2D::GetPosition() const
    {
        return this->Position;
    }

    void Entity2D::SetRotation(const float angle)
    {
        this->Entity::SetRotation(angle, Axis::Z);
    }

    void Entity2D::SetScaling(glm::vec2 scaling)
    {
        this->Entity::SetScaling({scaling.x, scaling.y, 1.0f});
    }

    void Entity2D::SetPosition(glm::vec2 newPosition)
    {
        this->Entity::SetPosition({newPosition.x, newPosition.y, 0.0f});
    }
    
    void Entity2D::Draw(const Color color)
    {
        const auto mat = this->GetMaterial();
        auto& renderer = Renderer::GetInstance();

        renderer.UpdateViewMatrix();
        const auto matrix = renderer.GetProjectionMatrix() * renderer.GetViewMatrix() * this->ModelMatrix;
        mat->UpdateGLMatrix(matrix, "matrix");

        if (mat->GetIsSolid())
        {
            renderer.Draw(mat->GetShaderProgram(), color);
        }
        else
        {
            renderer.Draw(mat->GetShaderProgram());
        }

    }

} // namespace basilisk
