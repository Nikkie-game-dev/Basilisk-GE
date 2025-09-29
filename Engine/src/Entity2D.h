#pragma once
#include "Colors.h"
#include "Entity.h"

namespace basilisk
{

    class BASILISK_API Entity2D : public Entity
    {
    public:
        /// <summary>
        /// Getter for rotation angle.
        /// </summary>
        /// <returns>Returns angle with X axis. Clockwise is positive.</returns>
        [[nodiscard]] float GetRotation2D() const;

        /// <summary>
        /// Getter for scale vector
        /// </summary>
        /// <returns>Returns 2D scale vector.</returns>
        [[nodiscard]] glm::vec2 GetScale2D() const;

        /// <summary>
        /// Getter for position vector
        /// </summary>
        /// <returns>Returns 2d position vector.</returns>
        [[nodiscard]] glm::vec2 GetPosition2D() const;

        /// <summary>
        /// Setter for rotation angle.
        /// </summary>
        /// <param name="angle">Angle to rotate entity. Clockwise is positive.</param>
        virtual void SetRotation(float angle);
        /// <summary>
        /// Setter for scale vector.
        /// </summary>
        /// <param name="scaling">Scaling vector.</param>
        virtual void SetScaling(glm::vec2 scaling);
        /// <summary>
        /// Setter for position vector.
        /// </summary>
        /// <param name="newPosition">Position vector</param>
        virtual void SetPosition(glm::vec2 newPosition);

        void Draw() override;

    protected:
        Entity2D() = default;
        virtual ~Entity2D() = default;

        Color Color = Color::Red;
    private:
        // These functions are private to make 2D entities use 2D corresponding functions
        [[nodiscard]] glm::vec3 GetPosition() const override;
        [[nodiscard]] glm::vec3 GetScale() const override;
        [[nodiscard]] glm::vec3 GetRotation() const override;
    };
} // namespace basilisk
