#pragma once
#include "Colors.h"
#include "Entity.h"

namespace basilisk
{

    class BASILISK_API Entity2D : public Entity
    {
    public:
        [[nodiscard]] float GetRotation2D() const;
        [[nodiscard]] glm::vec2 GetScale2D() const;
        [[nodiscard]] glm::vec2 GetPosition2D() const;
        
        virtual void SetRotation(float angle);
        virtual void SetScaling(glm::vec2 scaling);
        virtual void SetPosition(glm::vec2 newPosition);
        
    protected:
        Entity2D() = default;
        virtual ~Entity2D() = default;

        void Draw(Color color = Color::Red) override;

    private:
        [[nodiscard]] glm::vec3 GetPosition() const override;
        [[nodiscard]] glm::vec3 GetScale() const override;
        [[nodiscard]] glm::vec3 GetRotation() const override;
    };
} // namespace basilisk
