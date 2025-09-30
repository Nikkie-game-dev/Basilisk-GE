#include "Game.h"

namespace game
{
    Game::Game(const std::string& windowName, int sizeX, int sizeY) :
        BaseGame(windowName, sizeX, sizeY), Blue({sizeX, sizeY}, 10, 30)
    {
    }

    void Game::Init()
    {
        Blue.SetMaterial(basilisk::Material::New(true));
        Blue.Init();
    }

    void Game::Update()
    {
        Blue.Update();
    }

    void Game::Draw()
    {
        Blue.Draw();
    }
}
