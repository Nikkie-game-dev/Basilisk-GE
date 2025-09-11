#pragma once

#include "Export.h"

namespace basilisk
{
    class BASILISK_API Entity
    {
    public:
        Entity() = default;
        virtual ~Entity();

        virtual void Init() = 0;
        virtual void Update() = 0;
        
        void Draw() const;
        
        void UpdateBuffers() const;
        void FillVertices(float vertices[], int amountVertices);
        void FillIndices(unsigned int indices[], int amountIndices);
        
        bool IsActive = true;

    private:
        float* Vertices = nullptr;
        unsigned int* Indices = nullptr;
        int AmountVertices = 0;
        int AmountIndices = 0;
        
    };
} // basilisk 
