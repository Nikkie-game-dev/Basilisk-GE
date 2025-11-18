#include "Game.h"

#include <iostream>

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) : BaseGame(windowName, sizeX, sizeY), Player(100.0f)
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

        this->Player.SpinIA = &this->GetInputSystem().NewInput(basilisk::Keys::F);
        this->Player.PushIA = &this->GetInputSystem().NewInput(basilisk::Keys::G);

        auto obstacleMat = basilisk::Material::New(true);
        this->RedObstacle.SetMaterial(obstacleMat);
        this->RedObstacle.Init();
    }

    void Game::Update()
    {
        this->Player.Delta = this->GetDelta();
        this->RedObstacle.Delta = this->GetDelta();
        this->Player.Update();


        if (this->Player.GetNextPos())
        {
            if (basilisk::CollisionManager::IsCollidingAaBb(this->Player.NextPos, this->Player.GetScale2D(),
                                                            this->RedObstacle.GetPosition2D(), this->RedObstacle.GetScale2D()))
            {
                std::cout << "Hits" << std::endl;
                this->Player.ChangeAnimation(&this->Player.CollisionAnimation);
                //this->RedObstacle.GetPushed(this->Player.Speed * this->Player.Delta);
            }
            else
            {
                this->Player.Move();
            }
        }
        else
        {
            this->Player.ChangeAnimation(&this->Player.IdleAnimation);
        }

        this->RedObstacle.Update();
    }

    void Game::Draw()
    {
        this->Player.Draw();
        this->RedObstacle.Draw();
    }

    

} // namespace game
