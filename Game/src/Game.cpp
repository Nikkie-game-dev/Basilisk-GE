#include "Game.h"

Game::Game(const std::string& windowName, int sizeX, int sizeY) : 
	BaseGame(windowName, sizeX, sizeY), Renderer(Renderer::GetInstance())
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
    BaseGame::Draw();
}
