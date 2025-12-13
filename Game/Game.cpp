#include "Game.h"

#include <iostream>

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) :
        BaseGame(windowName, sizeX, sizeY), 
        Map("res/assets/map.json", "res/assets/spritesheet.png", {512, 1536}, {sizeX, sizeY}),
        Player(200.0f)
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

        this->Map.Init();
    }

    void Game::Update()
    {
        this->Map.CheckCollision(Player);
    }

    void Game::Draw()
    {
        this->Map.Draw();
    }

} // namespace game
