#include "Game.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) : 
        basilisk::BaseGame(windowName, sizeX, sizeY), Player(100.0f)
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

        this->Player.ScaleUpIA = &this->GetInputSystem().NewInput(basilisk::Keys::J);
        this->Player.ScaleDownIA = &this->GetInputSystem().NewInput(basilisk::Keys::K);

        this->Player.RotateCWIA = &this->GetInputSystem().NewInput(basilisk::Keys::Q);
        this->Player.RotateCCWIA = &this->GetInputSystem().NewInput(basilisk::Keys::E);
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
