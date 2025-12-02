#include "Obstacle.h"

namespace game
{
    Obstacle::Obstacle():
    Square({30,300},{100,100},true, basilisk::Color::Red)
    {
    }
    
    void Obstacle::Update()
    {
        if (this->Grow->IsDown())
        {
            this->SetScaling({this->GetScale2D().x + this->Speed * this->Delta,this->GetScale2D().y + this->Speed * this->Delta});
        }
        else if (this->Shrink->IsDown())
        {
            this->SetScaling({this->GetScale2D().x - this->Speed * this->Delta,this->GetScale2D().y - this->Speed * this->Delta});
        }
        if (this->RotateCW->IsDown())
        {
            this->SetRotation(this->GetRotation2D() + this->Speed * this->Delta);
        }
        else if (this->RotateCCW->IsDown())
        {
            this->SetRotation(this->GetRotation2D() - this->Speed * this->Delta);
        }
    }
}
