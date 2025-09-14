#include "Entity2D.h"

namespace basilisk
{

    Entity2D::Entity2D(const bool isSolid) : Entity(isSolid)
    {}
    
    glm::vec2 Entity2D::GetRotation() const
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
    
    void Entity2D::SetRotation(float angle)
    {
    }
    
    void Entity2D::SetRotation(glm::vec2 rotation)
    {
    }
    
    void Entity2D::SetScaling(glm::vec2 scaling)
    {
    }
    
    void Entity2D::SetScaling(float scale, Axis scalingAxis)
    {
    }
    
    void Entity2D::SetPosition(glm::vec2 newPosition)
    {
    }
}// namespace basilisk
