#pragma once
#include "Colors.h"
#include "Entity.h"

namespace basilisk
{
    
    class BASILISK_API Entity2D : public Entity
    {
    public:
        Entity2D() = default;
        virtual ~Entity2D() = default;

        [[nodiscard]] float GetRotation() const;
        [[nodiscard]] glm::vec2 GetScale() const;
        [[nodiscard]] glm::vec2 GetPosition() const;

        virtual void SetRotation(float angle);
        virtual void SetScaling(glm::vec2 scaling);
        virtual void SetPosition(glm::vec2 newPosition);
    protected:
        void Draw(Color color = Color::Red) override;
        
    };
} // namespace basilisk
