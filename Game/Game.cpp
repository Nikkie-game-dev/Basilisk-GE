#include "Game.h"

#include <iostream>

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) :
        BaseGame(windowName, sizeX, sizeY),
        Set({sizeX, sizeY})
    {
    }

    void Game::Init()
    {
    }

    void Game::Update()
    {
    }

    void Game::Draw()
    {
        this->Set.Draw();
    }

} // namespace game
