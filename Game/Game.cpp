#include "Game.h"

#include <iostream>

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) :
        BaseGame(windowName, sizeX, sizeY), Eirika("res/assets/Eirika_Lord_Sword_Sprite_Sheet.gif", {100, 300}, {200, 100}),
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
        
        this->Eirika.AttackAnimation.GenUVFrames({50, 200}, {40, 50}, {500, 250}, 1.0f, 10);
        this->Eliwood.AttackAnimation.GenUVFrames({210, 80}, {70, 80}, {500, 603}, 1.0f, 6);
        
        this->Eirika.IdleAnimation.GenUVFrames({0, 200}, {40, 50}, {500, 250}, 1, 1);
        this->Eliwood.IdleAnimation.GenUVFrames({395, 48}, {45, 60}, {500, 603}, 1, 2);

        this->Eirika.DeathAnimation.GenUVFrames({270, 160}, {40, 50}, {500, 250}, 1, 2);
        this->Eliwood.IdleAnimation.GenUVFrames({332, 80}, {45, 60}, {500, 603}, 1, 2);

        this->Eirika.Attack = &this->GetInputSystem().NewInput(Keys::A);
        this->Eliwood.Attack = &this->GetInputSystem().NewInput(Keys::K);
    }

    void Game::Update()
    {
        this->Eirika.Update();
        this->Eliwood.Update();
    }

    void Game::Draw()
    {
        this->Eirika.Draw();
        this->Eliwood.Draw();
    }

} // namespace game
