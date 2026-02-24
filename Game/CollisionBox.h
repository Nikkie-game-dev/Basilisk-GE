#pragma once
#include "Basilisk/Square.h"

namespace game
{
    class CollisionBox : public basilisk::Square
    {
    public:
        CollisionBox(glm::vec2 center, glm::vec2 size, basilisk::Color color);

        void Update() override;
    };

} // namespace game
