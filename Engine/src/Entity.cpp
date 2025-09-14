#include "Entity.h"
#include "GL/glew.h"
#include "Renderer.h"
#include "glm/gtc/type_ptr.hpp"
#include "Entity2D.h"

namespace basilisk
{
    Entity::~Entity()
    {
        delete[] this->Vertices;
        delete[] this->Indices;
    }

    void Entity::Draw() const
    {
        if (this->Vertices && this->Indices)
        {
            Renderer::GetInstance().UpdateModelMatrix(this->ModelMatrix);

            Renderer::GetInstance().Draw(this->AmountIndices);
        }
    }

    void Entity::UpdateBuffers() const
    {
        Renderer::GetInstance().GenerateVBs(this->Vertices, this->Indices, this->AmountVertices, this->AmountIndices);
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
    /// <param name="rotation"></param>
    void Entity::SetRotation(float angle, Axis rotationAxis)
    {
        switch (rotationAxis)
        {
        case basilisk::Axis::X:
            this->Rotation.x = angle;
            break;
        case basilisk::Axis::Y:
            this->Rotation.y = angle;
            break;
        case basilisk::Axis::Z:
            this->Rotation.z = angle;
            break;
        default:
            this->Rotation.z = angle;
            break;
        }

        UpdateRotationMatrix();
        UpdateModelMatrix();
    }

    void Entity::SetScaling(glm::vec3 scaling)
    {
        this->Scaling = scaling;
        this->ScaleMatrix = glm::scale(glm::mat4(1.0f), this->Scaling);
        UpdateModelMatrix();
    }

    void Entity::SetScaling(float scale, Axis scalingAxis)
    {
        switch (scalingAxis)
        {
        case basilisk::Axis::X:
            this->Scaling.x = scale;
            break;
        case basilisk::Axis::Y:
            this->Scaling.y = scale;
            break;
        case basilisk::Axis::Z:
            this->Scaling.z = scale;
            break;
        default:
            break;
        }

        SetScaling(this->Scaling);
    }

    /// <summary>
    /// Position is the top left corner of the entity
    /// </summary>
    /// <param name="newPosition"></param>
    void Entity::SetPosition(glm::vec3 newPosition)
    {
        this->Position = newPosition;

        UpdateTranslateMatrix();
        UpdateModelMatrix();
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
        auto rotation = glm::quat_cast(this->ModelMatrix);
        this->Rotation = glm::eulerAngles(rotation);
        this->Scaling = {glm::length(glm::vec3(this->ModelMatrix[0])), 
                         glm::length(glm::vec3(this->ModelMatrix[1])),
                         glm::length(glm::vec3(this->ModelMatrix[2]))};
    }
} // namespace basilisk
