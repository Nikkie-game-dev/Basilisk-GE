#include "Game.h"

#include <iostream>

#include "Basilisk/CollisionManager.h"

namespace game
{
    Game::Game(const char* windowName, float sizeX, float sizeY) :
        BaseGame(windowName, sizeX, sizeY),
        Map("res/assets/map.json", "res/assets/spritesheet.png", {512, 1536}, {sizeX, sizeY}),
        Player(100.0f, {Map.GetTileSize() * 2, Map.GetTileSize() * 2}, {600.0f, 500.0f})
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
        this->Player.Update();
        auto collisionDir = this->Map.CheckCollision(this->Player);

        glm::vec2 playerPos = this->Player.GetPosition2D();

        if (collisionDir.HorizontalDir != basilisk::CollisionManager::CollisionDir::NONE ||
            collisionDir.VerticalDir != basilisk::CollisionManager::CollisionDir::NONE)
        {
            const glm::vec2 collisionPos = Map.ConvertToScreenPos(collisionDir.CollisionTilePos);

            this->Logger->error("Collision detected: x: {}, y: {}\nPlayer screen position: x: {}, y: {}\nCollision layer: {}",
                               collisionDir.CollisionTilePos.x, collisionDir.CollisionTilePos.y, playerPos.x, playerPos.y, collisionDir.CollisionLayer);
        }

        this->Player.Delta = this->GetDelta();

        this->Player.CheckCollision(collisionDir);
    }

    void Game::Draw()
    {
        this->Map.Draw();
        this->Player.Draw();
    }

} // namespace game
