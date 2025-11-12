#include "Game.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) : 
        basilisk::BaseGame(windowName, sizeX, sizeY)
    {
    }
    
    void Game::Init()
    {
        auto playerMat = basilisk::Material::New(true);
        this->Player.SetMaterial(playerMat);
        this->Player.Init();
        this->Player.IdleAnimation.Play();
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
