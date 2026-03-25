#include "Game.h"

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) :
        BaseGame(windowName, sizeX, sizeY), 
        Player(100.0f, 10.0f, {64, 64}, {0.0f, 0.0f})
    {
    }

    void Game::Init()
    {
        auto playerMat = basilisk::Material::New(true);
        this->Player.SetMaterial(playerMat);
        this->Player.Init();

        this->Player.MoveUpIA = &this->GetInputSystem().NewInput(basilisk::Keys::W);
        this->Player.MoveLeftIA = &this->GetInputSystem().NewInput(basilisk::Keys::A);
        this->Player.MoveDownIA = &this->GetInputSystem().NewInput(basilisk::Keys::S);
        this->Player.MoveRightIA = &this->GetInputSystem().NewInput(basilisk::Keys::D);
        this->Player.MoveBack = &this->GetInputSystem().NewInput(basilisk::Keys::CTRL);
        this->Player.MoveFront = &this->GetInputSystem().NewInput(basilisk::Keys::SHIFT);
        this->Player.RotateLeft = &this->GetInputSystem().NewInput(basilisk::Keys::Q);
        this->Player.RotateRight = &this->GetInputSystem().NewInput(basilisk::Keys::E);
        
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
