#include "Game.h"

#include "Basilisk/Material.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) :
        BaseGame(windowName, sizeX, sizeY), Obstacle2({sizeX, sizeY})
    {
        this->Player.WalkUp = &this->GetInputSystem().NewInput(basilisk::Keys::W);
        this->Player.WalkLeft = &this->GetInputSystem().NewInput(basilisk::Keys::A);
        this->Player.WalkDown = &this->GetInputSystem().NewInput(basilisk::Keys::S);
        this->Player.WalkRight = &this->GetInputSystem().NewInput(basilisk::Keys::D);

        this->Obstacle.Shrink = &this->GetInputSystem().NewInput(basilisk::Keys::J);
        this->Obstacle.Grow = &this->GetInputSystem().NewInput(basilisk::Keys::K);
        this->Obstacle.RotateCW = &this->GetInputSystem().NewInput(basilisk::Keys::I);
        this->Obstacle.RotateCCW = &this->GetInputSystem().NewInput(basilisk::Keys::O);
    }

    void Game::Init()
    {
        auto mat = basilisk::Material::New(true);
        auto mat2 = basilisk::Material::New(false);
        this->Player.SetMaterial(mat);
        this->Obstacle.SetMaterial(mat2);
        this->Obstacle2.SetMaterial(mat2);

        this->Player.Init();
        this->Obstacle.Init();
        this->Obstacle2.Init();
    }

    void Game::Update()
    {
        this->Player.Delta = this->GetDelta();
        this->Obstacle.Delta = this->GetDelta();
        this->Obstacle2.Delta = this->GetDelta();

        this->Obstacle.Update();
        this->Obstacle2.Update();
        this->Player.Update();

        if (this->CM.IsCollidingAaBb(this->Player.GetPosition2D(), this->Player.GetScale2D(), this->Obstacle.GetPosition2D(),
                                     this->Obstacle.GetScale2D()))
        {
            this->Player.SetPosition(this->Player.OldPosition);
            this->Player.NewPosition = this->Player.OldPosition;
        }
        else
        {
            this->Player.SetPosition(this->Player.NewPosition);
            this->Player.OldPosition = this->Player.NewPosition;
        }

    }

    void Game::Draw()
    {
        this->Player.Draw();
        this->Obstacle.Draw();
        this->Obstacle2.Draw();
    }

} // namespace game
