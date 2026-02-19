#include "CollisionBox.h"

namespace game
{
    CollisionBox::CollisionBox(glm::vec2 center, glm::vec2 size, basilisk::Color color) : 
        Square(center, size, true, color)
    {
    }

    void CollisionBox::Update()
    {
    }

} // namespace game
