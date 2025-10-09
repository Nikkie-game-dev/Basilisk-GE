#include "Game.h"

namespace game
{
    Game::Game(const std::string& windowName, int sizeX, int sizeY) :
        BaseGame(windowName, sizeX, sizeY), Test(TestTriangle({50, 100}, {100,100})), 
                                            Test2(GreenSquare({50.0f, 100.0f}, {100,100}))
    {
    }

    void Game::Init()
    {
        auto mat = basilisk::Material::New(true);
        Test2.SetMaterial(mat);
        Test2.Init();
        Test.SetMaterial(mat);
        Test.Init();
    }

    void Game::Update()
    {
        Test2.Delta = this->GetDelta();
        Test2.Update();
        Test.Update();
    }

    void Game::Draw()
    {
        Test2.Draw();
        Test.Draw();
    }
}
