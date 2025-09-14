#include "Game.h"

namespace game
{
    Game::Game(const std::string& windowName, int sizeX, int sizeY) : 
        BaseGame(windowName, sizeX, sizeY), Test({1,0})
    {
    }

    void Game::Init()
    {
        Test.Init();
    }

    void Game::Update()
    {
    }

    void Game::Draw()
    {
        Test.Draw();
    }
}
