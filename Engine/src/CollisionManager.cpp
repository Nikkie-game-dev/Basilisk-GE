#include "CollisionManager.h"
bool basilisk::CollisionManager::IsCollidingAaBb(const glm::vec2 positionA,
                                             const glm::vec2 sizeA,
                                             const glm::vec2 positionB,
                                             const glm::vec2 sizeB)
{
    const glm::vec2 aBottomLeft = {positionA.x - sizeA.x / 2, positionA.y - sizeA.y / 2};
    const glm::vec2 bBottomLeft = {positionB.x - sizeB.x / 2, positionB.y - sizeB.y / 2};


    return aBottomLeft.x < bBottomLeft.x + sizeB.x
        && aBottomLeft.x + sizeA.x > bBottomLeft.x
        && aBottomLeft.y < bBottomLeft.y + sizeB.y
        && aBottomLeft.y + sizeA.y > bBottomLeft.y;

}
