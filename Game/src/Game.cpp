#include "Game.h"

namespace game
{
    Game::Game(const std::string& windowName, int sizeX, int sizeY) :
        BaseGame(windowName, sizeX, sizeY), Test(OrangeSquare({50.0f, 100.0f}, {100,100}, 0)), 
                                            Test2(GreenSquare({50.0f, 100.0f}, {100,100}, 0))
    {
    }

    void Game::Init()
    {
        Test2.SetMaterial(basilisk::Material::New(true));
        Test2.Init();
        Test.SetMaterial(basilisk::Material::New(true));
        Test.Init();
    }

    void Game::Update()
    {
        Test2.Update();
        Test.Update();
    }

    void Game::Draw()
    {
        Test2.Draw();
        Test.Draw();
    }
}
