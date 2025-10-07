#include "GreenSquare.h"

namespace game
{
    GreenSquare::GreenSquare(const glm::vec2& size, const glm::vec2& position) :
        Square(position, size, true, basilisk::Color::Green)
    {
    }

    void GreenSquare::Update()
    {
        auto rot = GetRotation2D();
        SetRotation(rot - 30);

        static bool growing = false;
        auto scale = GetScale2D();
        if (scale.x > 50)
        {
            growing = false;
        }
        else if (scale.x < 10)
        {
            growing = true;
        }

        if (growing)
        {
            SetScaling({scale.x + 1, scale.y + 1});
        }
        else
        {
            SetScaling({scale.x - 1, scale.y - 1});
        }
    }
} // namespace game
