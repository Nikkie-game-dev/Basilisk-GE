#include "Samus.h"

namespace game
{

    Samus::Samus():
        Sprite("res/assets/Samus Aran Sprite Sheet.png", {300,300}, {100,100})
    {
        this->IdleAnim.GenUVFrames({28,650}, {65,72}, {860,762}, 1.0f, 5);
        this->LeftAnim.GenUVFrames({20,481}, {82, 72}, {860,762}, 1.0f, 10);
        this->SetAnimation(&this->IdleAnim);
        this->CurrentAnimation = &this->IdleAnim;
        this->OldAnimation =  &this->IdleAnim;
        this->OldPosition = {300,300};
        this->NewPosition = {300,300};
    }

    void Samus::Update()
    {
        auto pos = this->GetPosition2D();
        
        if (this->WalkLeft->IsDown())
        {
            this->CurrentAnimation = &this->LeftAnim;
            this->NewPosition = {pos.x - this->Speed * this->Delta, pos.y};
        }
        else if (this->WalkRight->IsDown())
        {
            this->CurrentAnimation = &this->LeftAnim;
            this->NewPosition = {pos.x + this->Speed * this->Delta, pos.y};
        }
        else if (this->WalkDown->IsDown())
        {
            this->CurrentAnimation = &this->LeftAnim;
            this->NewPosition ={pos.x, pos.y - this->Speed * this->Delta};
        }
        else if (this->WalkUp->IsDown())
        {
            this->CurrentAnimation = &this->LeftAnim;
            this->NewPosition ={pos.x, pos.y + this->Speed * this->Delta};
        }
        else
        {
            this->CurrentAnimation = &this->IdleAnim;
        }

        this->UpdateAnimation(this->Delta);
        if (this->CurrentAnimation->GetId() != this->OldAnimation->GetId())
        {
            ChangeAnimation(this->CurrentAnimation);
        }
        this->OldAnimation = this->CurrentAnimation;
    }

}
