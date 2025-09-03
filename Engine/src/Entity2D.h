#pragma once
#include "src/Entity.h"
#include "src/math/Vec2.h"

namespace basilisk
{
    enum class Axis
    {
        X,
        Y,
    };
    
    class BASILISK_API Entity2D : Entity
    {
    public:
        void Rotate(float angle);
        void Scale(float scale, Axis scalingAxis);

        [[nodiscard]] float GetRotation() const
        {
            return Rotation;
        }
        
        [[nodiscard]] math::Vec2<float> GetScale() const
        {
            return Scaling;
        }
        
        math::Vec2<float> Position = {0,0};
        
    private:
        math::Vec2<float> Scaling = {1,1};
        float Rotation = 0;
    };
} // basilisk 
