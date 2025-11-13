#include "Game.h"

#include <iostream>

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) :
        BaseGame(windowName, sizeX, sizeY), Player(100.0f)
    {
    }

    void Game::Init()
    {
        auto playerMat = basilisk::Material::New(true);
        this->Player.SetMaterial(playerMat);
        this->Player.Init();

        this->Player.MoveUpIA = &this->GetInputSystem().NewInput(basilisk::Keys::W);
        this->Player.MoveLeftIA = &this->GetInputSystem().NewInput(basilisk::Keys::A);
        this->Player.MoveDownIA = &this->GetInputSystem().NewInput(basilisk::Keys::S);
        this->Player.MoveRightIA = &this->GetInputSystem().NewInput(basilisk::Keys::D);

        this->Player.ScaleUpIA = &this->GetInputSystem().NewInput(basilisk::Keys::J);
        this->Player.ScaleDownIA = &this->GetInputSystem().NewInput(basilisk::Keys::K);

        this->Player.RotateCWIA = &this->GetInputSystem().NewInput(basilisk::Keys::Q);
        this->Player.RotateCCWIA = &this->GetInputSystem().NewInput(basilisk::Keys::E);

        auto obstacleMat = basilisk::Material::New(false);
        this->RedObstacle.SetMaterial(obstacleMat);
        this->RedObstacle.Init();
        
        this->BlueObstacle.SetMaterial(obstacleMat);
        this->BlueObstacle.Init();
    }

    void Game::Update()
    {
        this->BlueObstacle.SetPosition(this->Player.GetPosition2D());
        
        this->Player.Delta = this->GetDelta();
        this->Player.Update();
        
        if (basilisk::CollisionManager::IsCollidingAaBb(this->Player.GetPosition2D(),
                                                        this->Player.GetScale2D(),
                                                        this->RedObstacle.GetPosition2D(),
                                                        this->RedObstacle.GetScale2D()))
        {
            std::cout << "Hits" << std::endl;
        }
    }

    void Game::Draw()
    {
        this->BlueObstacle.Draw();
        this->Player.Draw();
        this->RedObstacle.Draw();
    }

} // namespace game
