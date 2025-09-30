#include "BlueSquare.h"

#include <numbers>

namespace game
{

    
    BlueSquare::BlueSquare(glm::vec2 screenSize, float speed, float rotSpeed):
        Square({0,0}, {50, 50}, true, basilisk::Color::Blue)
    {
        this->Margin = 35;
        Entity2D::SetPosition({this->Margin, screenSize.y - this->Margin});
        this->Speed = speed;
        this->RotSpeed = rotSpeed;
        this->ScreenSize = screenSize;
    }
    
    void BlueSquare::Update()
    {
        const auto pos = this->GetPosition2D();
        if (pos.x <= this->ScreenSize.x - this->Margin && pos.x >= Margin)
        {
            if ( pos.y >= this->ScreenSize.y - this->Margin - FLT_EPSILON)
            {
                this->SetPosition({pos.x + this->Speed, pos.y});
            }
            else if ( pos.y >= this->Margin + FLT_EPSILON)
            {
                this->SetPosition({pos.x, pos.y - this->Speed});
            }
        }
        else if (pos.x <= this->ScreenSize.x + this->Margin)
        {
            if ( pos.y >= this->ScreenSize.y - this->Margin - FLT_EPSILON)
            {
                this->SetPosition({pos.x, pos.y - this->Speed});
            }
            else if ( pos.y >= this->Margin + FLT_EPSILON)
            {
                this->SetPosition({pos.x - this->Speed, pos.y});
            }
        }
        else if (pos.x >= this->Margin)
        {
            if ( pos.y >= this->ScreenSize.y - this->Margin - FLT_EPSILON)
            {
                this->SetPosition({pos.x + this->Speed, pos.y });
            }
            else if ( pos.y >= this->Margin + FLT_EPSILON)
            {
                this->SetPosition({pos.x , pos.y + this->Speed});
            }
        }

        this->SetRotation(this->GetRotation2D() - (this->Speed / 2 * std::numbers::pi_v<float>));
    }
}
