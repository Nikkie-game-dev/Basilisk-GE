#include "Entity.h"

#include "RenderException.h"
#include "Renderer.h"
#include "glm/gtc/type_ptr.hpp"

namespace basilisk
{

    Entity::~Entity()
    {
        delete[] this->Vertices;
        delete[] this->Indices;
    }

    void Entity::UpdateBuffers() const
    {
        Renderer::GetInstance().GenerateVBs(this->Vertices, this->Indices, this->AmountVertices, this->AmountIndices, this->GetMaterial()->GetIsSolid());
    }

    glm::mat4 Entity::GetModelMatrix() const
    {
        return this->ModelMatrix;
    }

    void Entity::FillVertices(float vertices[], const int amountVertices)
    {
        delete[] this->Vertices;

        this->Vertices = new float[amountVertices];

        for (int i = 0; i < amountVertices; ++i)
        {
            this->Vertices[i] = vertices[i];
        }

        this->AmountVertices = amountVertices;
    }

    void Entity::FillIndices(unsigned int indices[], const int amountIndices)
    {
        delete[] this->Indices;

        this->Indices = new unsigned int[amountIndices];

        for (int i = 0; i < amountIndices; ++i)
        {
            this->Indices[i] = indices[i];
        }

        this->AmountIndices = amountIndices;
    }

    /// <summary>
    /// Negative values rotate counter clockwise
    /// </summary>
    /// <param name="angle"></param>
    /// <param name="rotationAxis"></param>
    void Entity::SetRotation(const float angle, const Axis rotationAxis)
    {
        switch (rotationAxis)
        {
        case Axis::X:
            this->Rotation.x = angle;
            break;
        case Axis::Y:
            this->Rotation.y = angle;
            break;
        default:
            this->Rotation.z = angle;
            break;
        }

        UpdateRotationMatrix();
        UpdateModelMatrix();
    }

    void Entity::SetScaling(const glm::vec3& scaling)
    {
        this->Scaling = scaling;
        this->ScaleMatrix = glm::scale(glm::mat4(1.0f), this->Scaling);
        UpdateModelMatrix();
    }

    void Entity::SetScaling(const float scale, const Axis scalingAxis)
    {
        switch (scalingAxis)
        {
        case Axis::X:
            this->Scaling.x = scale;
            break;
        case Axis::Y:
            this->Scaling.y = scale;
            break;
        case Axis::Z:
            this->Scaling.z = scale;
            break;

        }

        SetScaling(this->Scaling);
    }

    /// <summary>
    /// Position is the top left corner of the entity
    /// </summary>
    /// <param name="newPosition"></param>
    void Entity::SetPosition(const glm::vec3& newPosition)
    {
        this->Position = newPosition;

        UpdateTranslateMatrix();
        UpdateModelMatrix();
    }

    void Entity::SetMaterial(const std::shared_ptr<Material>& material)
    {
        // When shared_ptr is in rhs, it inits the shared_ptr in lhs and increments one ref count. When ref count == 0, the object referenced
        // is deleted.
        this->Mat = material;
    }

    std::shared_ptr<Material> Entity::GetMaterial() const
    {
        if (!Mat)
        {
            throw MaterialUnassigned();
        }
        return Mat;

    }

    void Entity::UpdateRotationMatrix()
    {
        this->RotationMatrix = glm::mat4(1.0f);
        if (Rotation.x != 0.0f)
            this->RotationMatrix = glm::rotate(this->RotationMatrix, glm::radians(this->Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

        if (Rotation.y != 0.0f)
            this->RotationMatrix = glm::rotate(this->RotationMatrix, glm::radians(this->Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

        if (Rotation.z != 0.0f)
            this->RotationMatrix = glm::rotate(this->RotationMatrix, glm::radians(this->Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void Entity::UpdateTranslateMatrix()
    {
        this->TranslateMatrix = glm::translate(glm::mat4(1.0f), this->Position);
    }

    void Entity::UpdateModelMatrix()
    {
        this->ModelMatrix = this->TranslateMatrix * this->RotationMatrix * this->ScaleMatrix;
        this->Position = glm::vec3(this->ModelMatrix[3]);
        const auto rotation = glm::quat_cast(this->ModelMatrix);
        this->Rotation = glm::eulerAngles(rotation);
        this->Scaling = {glm::length(glm::vec3(this->ModelMatrix[0])),
                         glm::length(glm::vec3(this->ModelMatrix[1])),
                         glm::length(glm::vec3(this->ModelMatrix[2]))};

    }
} // namespace basilisk
