#include "TransparentObs.h"

namespace game
{
    TransparentObs::TransparentObs(glm::vec2 screenSize) :
        Square({300, 300}, {300, 300}, true, basilisk::Color(0, 0, 255, 0.5f))
    {
        this->ScreenSize = screenSize;
    }

    void TransparentObs::Update()
    {
        auto pos = this->GetPosition2D();

        if (pos.x <= 0)
        {
            this->GoLeft = false;
        }
        else if (pos.x >= ScreenSize.x)
        {
            this->GoLeft = true;
        }


        this->SetPosition({pos.x + (this->GoLeft ? -1.0f : 1.0f) * this->Speed * this->Delta, pos.y});

    }
}
