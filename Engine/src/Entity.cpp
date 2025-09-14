#include "Entity.h"

#include "Renderer.h"

namespace basilisk
{
    Entity::Entity(const bool isSolidColor) : Mat(isSolidColor)
    {}
    
    Entity::~Entity()
    {
        delete[] this->Vertices;
        delete[] this->Indices;
    }
    
    void Entity::UpdateBuffers() const
    {
        Renderer::GetInstance().GenerateVBs(this->Vertices, this->Indices, this->AmountVertices, this->AmountIndices, Mat.GetIsSolid());
    }
    
    void Entity::FillVertices(float vertices[], const int amountVertices)
    {
        delete[] this->Vertices;
        
        this->Vertices = new float[amountVertices];

        for (int i = 0; i < amountVertices; ++i)
        {
            this->Vertices[i]  = vertices[i];
        }

        this->AmountVertices = amountVertices;
    }
    
    void Entity::FillIndices(unsigned int indices[], const int amountIndices)
    {
        delete[] this->Indices;
        
        this->Indices = new unsigned int[amountIndices];

        for (int i = 0; i < amountIndices; ++i)
        {
            this->Indices[i]  = indices[i];
        }
        
        this->AmountIndices = amountIndices;
        
    }
} // namespace basilisk
