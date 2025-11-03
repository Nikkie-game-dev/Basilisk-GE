#include "Game.h"

namespace game
{
    Game::Game(const char* windowName, int sizeX, int sizeY) :
        BaseGame(windowName, sizeX, sizeY),
        Test(TestTriangle({50, 100}, {100, 100})),
        Test2(GreenSquare({50.0f, 100.0f}, {100, 100})),
        Test3(TextureTest()),
        Test4({20, 20}, { 100, 600})
    {
        
    }

    void Game::Init()
    {
        auto mat = basilisk::Material::New(false);
        Test2.SetMaterial(mat);
        Test2.Init();
        
        Test.SetMaterial(mat);
        Test.Init();
        
        auto mat2 = basilisk::Material::New(true);
        Test3.SetMaterial(mat2);
        Test3.Init();
        
        Test4.SetMaterial(mat);
        Test4.Init();
        Test4.Action = &this->GetInputSystem().NewInput(basilisk::Keys::A);
    
        auto mat3 = basilisk::Material::New(true);
        Test5.SetMaterial(mat3);
        Test5.Init();
    }

    void Game::Update()
    {
        Test2.Delta = this->GetDelta();
        Test3.Delta = this->GetDelta();
        Test5.Delta = this->GetDelta();
        Test2.Update();
        Test.Update();
        Test3.Update();
        Test4.Update();
        Test5.Update();
    }

    void Game::Draw()
    {
        Test2.Draw();
        Test.Draw();
        Test3.Draw();
        Test4.Draw();
        Test5.Draw();
    }
}
