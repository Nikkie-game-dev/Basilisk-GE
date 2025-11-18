#include "Game.h"

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) :
        BaseGame(windowName, sizeX, sizeY), Eirika("res/assets/Eirika_Lord_Sword_Sprite_Sheet.gif", {150, 300}, {200, 100}),
        Eliwood("res/assets/Eliwood_Knightlord_Lance_Sprite_Sheet.gif", {400, 300}, {100, 100})
    {
    }

    void Game::Init()
    {
        auto mat = Material::New(true);

        this->Eliwood.SetMaterial(mat);
        this->Eirika.SetMaterial(mat);

        this->Eliwood.Init();
        this->Eirika.Init();

        this->Eirika.AttackAnimation.GenUVFrames({39, 205}, {39, 45}, {500, 250}, 1.5f, 10);
        this->Eliwood.AttackAnimation.GenUVFrames({0, 19}, {65, 85}, {500, 603}, 1, 4);

        this->Eirika.IdleAnimation.GenUVFrames({0, 200}, {40, 50}, {500, 250}, 0.3f, 1);
        this->Eliwood.IdleAnimation.GenUVFrames({396 , 42}, {50, 60}, {500, 603}, 0.3f, 2);

        this->Eirika.DeathAnimation.GenUVFrames({270, 160}, {40, 50}, {500, 250}, 0.3f, 2);
        this->Eliwood.DeathAnimation.GenUVFrames({332, 80}, {45, 60}, {500, 603}, 0.3f, 2);

        this->Eirika.Attack = &this->GetInputSystem().NewInput(Keys::A);
        this->Eliwood.Attack = &this->GetInputSystem().NewInput(Keys::K);

        this->Eirika.FlipSpriteX = true;

        this->Eirika.SetAnimation(&this->Eirika.IdleAnimation);
        this->Eliwood.SetAnimation(&this->Eliwood.IdleAnimation);

        this->Eirika.IdleAnimation.Play();
        this->Eliwood.IdleAnimation.Play();

        this->Eliwood.DeathTimer = 1;
        this->Eliwood.AttackTimer = 1;

        this->Eirika.DeathTimer = 1;
        this->Eirika.AttackTimer = 1.5f;
    }

    void Game::Update()
    {
        this->Eirika.Delta = this->GetDelta();
        this->Eliwood.Delta = this->GetDelta();

        this->Eirika.Update();
        this->Eliwood.Update();

        if (this->Eirika.Attack->IsPressedAndReleased())
        {
            this->Eliwood.IsGettingAttacked = true;
        }
        else if (this->Eliwood.Attack->IsPressedAndReleased())
        {
            this->Eirika.IsGettingAttacked = true;
        }
    }

    void Game::Draw()
    {
        this->Eirika.Draw();
        this->Eliwood.Draw();
    }

} // namespace game
