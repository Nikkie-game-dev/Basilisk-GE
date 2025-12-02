#include "Game.h"

#include <iostream>

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) : BaseGame(windowName, sizeX, sizeY), Player(100.0f)
    {
    }

    void Game::Init()
    {
        auto playerMat = basilisk::Material::New(true);
        this->Player.SetMaterial(playerMat);
        this->Player.Init();

        this->Player.MoveLeftIA = &this->GetInputSystem().NewInput(basilisk::Keys::A);
        this->Player.MoveRightIA = &this->GetInputSystem().NewInput(basilisk::Keys::D);

    }

    void Game::Update()
    {
        this->Player.Delta = this->GetDelta();
        this->Player.Update();


    }

    void Game::Draw()
    {
        this->Player.Draw();
    }


} // namespace game
