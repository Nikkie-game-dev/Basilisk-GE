#include "Game.h"

#include <iostream>

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) : 
        BaseGame(windowName, sizeX, sizeY), 
        Player(100.0f), RedSquare(100.0f), BlueSquare(200.0f, {sizeX, sizeY})
    {
    }

    void Game::Init()
    {
        auto playerMat = basilisk::Material::New(true);
        this->Player.SetMaterial(playerMat);
        this->Player.Init();

        this->Player.MoveLeftIA = &this->GetInputSystem().NewInput(basilisk::Keys::A);
        this->Player.MoveRightIA = &this->GetInputSystem().NewInput(basilisk::Keys::D);

        auto redSquareMat = basilisk::Material::New(false);
        this->RedSquare.SetMaterial(redSquareMat);
        this->RedSquare.Init();

        this->RedSquare.ScaleUp = &this->GetInputSystem().NewInput(basilisk::Keys::U);
        this->RedSquare.ScaleDown = &this->GetInputSystem().NewInput(basilisk::Keys::I);
        this->RedSquare.RotateCCW = &this->GetInputSystem().NewInput(basilisk::Keys::J);
        this->RedSquare.RotateCW = &this->GetInputSystem().NewInput(basilisk::Keys::K);

        auto blueSquareMat = basilisk::Material::New(false);
        this->BlueSquare.SetMaterial(blueSquareMat);
        this->BlueSquare.Init();
    }

    void Game::Update()
    {
        this->Player.Delta = this->GetDelta();
        this->RedSquare.Delta = this->GetDelta();
        this->BlueSquare.Delta = this->GetDelta();
        this->Player.Update();


        if (this->Player.GetNextPos())
        {
            if (basilisk::CollisionManager::IsCollidingAaBb(this->Player.NextPos, this->Player.GetScale2D(),
                                                            this->RedSquare.GetPosition2D(), this->RedSquare.GetScale2D()))
            {
                std::cout << "Hits" << std::endl;
                // this->RedObstacle.GetPushed(this->Player.Speed * this->Player.Delta);
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

        this->RedSquare.Update();
        this->BlueSquare.Update();
    }

    void Game::Draw()
    {
        this->Player.Draw();
        this->RedSquare.Draw();
        this->BlueSquare.Draw();
    }


} // namespace game
