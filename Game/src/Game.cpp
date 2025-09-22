#include "Game.h"

namespace game
{
    Game::Game(const std::string& windowName, int sizeX, int sizeY) : 
        BaseGame(windowName, sizeX, sizeY), Test(OrangeSquare({1.0f, 1.0f}, {0.0f, 0.0f}, 20.0f))
    {
    }

    void Game::Init()
    {
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
