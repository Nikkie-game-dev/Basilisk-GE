#include "Game.h"

namespace game
{
    Game::Game(const std::string& windowName, int sizeX, int sizeY) :
        BaseGame(windowName, sizeX, sizeY), Test(OrangeSquare({100.0f, 100.0f}, {10,110}, 0))
    {
    }

    void Game::Init()
    {
        Test.SetMaterial(basilisk::Material::New(true)); //HACK: this is only for testing, Test should probably store if it is solid or not
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
