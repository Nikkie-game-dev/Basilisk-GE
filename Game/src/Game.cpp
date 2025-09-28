#include "Game.h"

namespace game
{
    Game::Game(const std::string& windowName, int sizeX, int sizeY) :
        BaseGame(windowName, sizeX, sizeY), Test(OrangeSquare({10000.0f, 10000.0f}, {-100,100}, 0))
    {
    }

    void Game::Init()
    {
        Test.SetMaterial(basilisk::Material::New(true));
        Test.Init();
    }

    void Game::Update()
    {
        Test.Update();
    }

    void Game::Draw()
    {
        Test.Draw();
    }
}
