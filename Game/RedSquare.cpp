#include "RedSquare.h"
namespace game
{
    RedSquare::RedSquare(float speed) : Square({400, 300}, {100,100}, true, basilisk::Color::Red)
    {
        Speed = speed;
        Delta = 0.0f;
    }

    void RedSquare::Update()
    {
        auto scale = GetScale2D();
        auto rotat = GetRotation2D();

        if (this->ScaleUp && this->ScaleUp->IsDown())
        {
            scale.x += Speed * Delta;
            scale.y += Speed * Delta;
        }
        else if (this->ScaleDown && this->ScaleDown->IsDown())
        {
            scale.x -= Speed * Delta;
            scale.y -= Speed * Delta;
        }
        else if (this->RotateCCW && this->RotateCCW->IsDown())
        {
            rotat += Speed * Delta;

        }
        else if (this->RotateCW && this->RotateCW->IsDown())
        {
            rotat -= Speed * Delta;
        }

        SetRotation(rotat);
        SetScaling(scale);
    }
} // namespace game
