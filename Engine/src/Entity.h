#pragma once

#include "Export.h"

namespace basilisk
{
    class BASILISK_API Entity
    {
    public:
        Entity();
        virtual ~Entity() = default;
        
        virtual void Update() = 0;
        virtual void Draw() = 0;
        
        bool IsActive;
    };
} // basilisk 
