#include "CollisionManager.h"

#include "Log.h"

namespace basilisk
{
    bool CollisionManager::IsCollidingAaBb(const glm::vec2& positionA,
                                           const glm::vec2& sizeA,
                                           const glm::vec2& positionB,
                                           const glm::vec2& sizeB)
    {
        const glm::vec2 aBottomLeft = {positionA.x - sizeA.x / 2, positionA.y - sizeA.y / 2};
        const glm::vec2 bBottomLeft = {positionB.x - sizeB.x / 2, positionB.y - sizeB.y / 2};


        return aBottomLeft.x < bBottomLeft.x + sizeB.x && aBottomLeft.x + sizeA.x > bBottomLeft.x &&
            aBottomLeft.y < bBottomLeft.y + sizeB.y && aBottomLeft.y + sizeA.y > bBottomLeft.y;
    }

    CollisionManager::CollisionData CollisionManager::GetCollisionDir(const glm::vec2& positionA, const glm::vec2& positionB)
    {
        CollisionData data;

        glm::vec2 vector = positionB - positionA;
        const float hypotenuse = sqrtf(powf(vector.x, 2) + powf(vector.y, 2));

        vector = {vector.x / hypotenuse, vector.y / hypotenuse};

        if (abs(vector.x) >= abs(vector.y))
        {
            if (vector.x > 0)
            {
                data.HorizontalDir = CollisionDir::RIGHT;
            }
            else if (vector.x < 0)
            {
                data.HorizontalDir = CollisionDir::LEFT;
            }
        }
        else if (abs(vector.x) < abs(vector.y))
        {
            if (vector.y > 0)
            {
                data.VerticalDir = CollisionDir::UP;
            }
            else if (vector.y < 0)
            {
                data.VerticalDir = CollisionDir::DOWN;
            }
        }

        if (data.VerticalDir == CollisionDir::NONE && data.HorizontalDir == CollisionDir::NONE)
        {
            Log::Print()->error("A collision  with none direction was detected. Position A: ({}, {})\n,  Position B: ({}, {})",
                                positionA.x, positionA.y, positionB.x, positionB.y);
        }

        return data;
    }

} // namespace basilisk
