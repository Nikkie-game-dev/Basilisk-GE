#include "CollisionManager.h"

namespace basilisk
{

    bool CollisionManager::IsCollidingAaBb(const glm::vec2 positionA, const glm::vec2 sizeA, const glm::vec2 positionB, const glm::vec2 sizeB)
    {
        const glm::vec2 aBottomLeft = {positionA.x - sizeA.x / 2, positionA.y - sizeA.y / 2};
        const glm::vec2 bBottomLeft = {positionB.x - sizeB.x / 2, positionB.y - sizeB.y / 2};


        return aBottomLeft.x < bBottomLeft.x + sizeB.x && aBottomLeft.x + sizeA.x > bBottomLeft.x &&
            aBottomLeft.y < bBottomLeft.y + sizeB.y && aBottomLeft.y + sizeA.y > bBottomLeft.y;
    }

    CollisionManager::CollisionData CollisionManager::GetCollisionDir(const glm::vec2 positionA, const glm::vec2 sizeA, const glm::vec2 positionB, const glm::vec2 sizeB)
    {
        CollisionData data;

        const glm::vec2 halfA = sizeA * 0.5f;
        const glm::vec2 halfB = sizeB * 0.5f;

        const glm::vec2 distance = positionA - positionB;

        const float overlapX = (halfA.x + halfB.x) - std::abs(distance.x);
        const float overlapY = (halfA.y + halfB.y) - std::abs(distance.y);

        if (overlapX <= 0.0f || overlapY <= 0.0f)
            return data;

        if (overlapX < overlapY)
        {
            data.HorizontalDir = distance.x > 0.0f ? CollisionDir::RIGHT : CollisionDir::LEFT;
        }
        else
        {
            data.VerticalDir = distance.y > 0.0f ? CollisionDir::DOWN : CollisionDir::UP;
        }
        
        return data;
    }

} // namespace basilisk
