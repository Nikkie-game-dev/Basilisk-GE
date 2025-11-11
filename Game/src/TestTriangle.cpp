#include "TestTriangle.h"

namespace game
{

    TestTriangle::TestTriangle(const glm::vec2& size, const glm::vec2& position) : 
        Triangle(position, size, true, basilisk::Color::Purple)
    {
    }
    
    void TestTriangle::Update()
    {
        auto rot = GetRotation2D();
        SetRotation( rot + 3 * this->Delta);

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
            SetScaling({scale.x + 1 * this->Delta, scale.y + 1 * this->Delta});
        }
        else
        {
            SetScaling({scale.x - 1 * this->Delta, scale.y - 1 * this->Delta});
        }
    }
}
