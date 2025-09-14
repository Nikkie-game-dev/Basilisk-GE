#include "Entity2D.h"
#include "glm/gtc/type_ptr.hpp"
#include "GL/glew.h"

namespace basilisk
{

    float Entity2D::GetRotation() const
    {
        return this->Rotation;
    }

    glm::vec2 Entity2D::GetScale() const
    {
        return this->Scaling;
    }

    glm::vec2 Entity2D::GetPosition() const
    {
        return this->Position;
    }

    /// <summary>
    /// Negative values rotate counter clockwise
    /// </summary>
    /// <param name="rotation"></param>
    void Entity2D::SetRotation(float angle)
    {
        this->Rotation = angle;
        UpdateRotationMatrix();
        UpdateModelMatrix();
    }

    void Entity2D::SetScaling(glm::vec2 scaling)
    {
        this->Scaling = scaling;
        this->ScaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(this->Scaling, 1.0f));
        UpdateModelMatrix();
    }

    void Entity2D::SetScaling(float scale, Axis scalingAxis)
    {
        if (scalingAxis == Axis::X)
            this->Scaling.x = scale;
        else
            this->Scaling.y = scale;

        SetScaling(this->Scaling);
    }

    /// <summary>
    /// Position is the top left corner of the entity
    /// </summary>
    /// <param name="newPosition"></param>
    void Entity2D::SetPosition(glm::vec2 newPosition)
    {
        this->Position = newPosition;

        UpdateTranslateMatrix();
        UpdateModelMatrix();

    }

    void Entity2D::UpdateRotationMatrix()
    {
        this->RotationMatrix = glm::mat4(1.0f);
        this->RotationMatrix = glm::rotate(this->RotationMatrix, glm::radians(this->Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void Entity2D::UpdateTranslateMatrix()
    {
        this->TranslateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->Position, 0.0f));
    }

    void Entity2D::UpdateModelMatrix()
    {
        this->ModelMatrix = this->TranslateMatrix * this->RotationMatrix * this->ScaleMatrix;
        this->Position = glm::vec2(this->ModelMatrix[3]);
        auto rotation = glm::quat_cast(this->ModelMatrix);
        this->Rotation = glm::eulerAngles(rotation).z;
        this->Scaling = glm::vec2(glm::length(glm::vec2(this->ModelMatrix[0])), glm::length(glm::vec2(this->ModelMatrix[1])));
    
        
    }

} // namespace basilisk
