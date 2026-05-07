#include "Game.h"

#include "Basilisk/Log.h"

namespace game
{
    enum class CameraNames : unsigned short
    {
        FirstPerson,
        ThirdPerson
    };

    Game::Game(const char* windowName, float sizeX, float sizeY) :
        BaseGame(windowName, sizeX, sizeY), RotCube(true, {10, 10, 10}, {10, 10, 10}, basilisk::Color::Red)
    {
    }

    void Game::Init()
    {
        auto& renderer = basilisk::Renderer::GetInstance();

        renderer.AddCamera(FirstPerson);
        renderer.AddCamera(ThirdPerson);

        renderer.SetCameraActive(static_cast<unsigned>(CameraNames::ThirdPerson));

        const auto mat = basilisk::Material::New(false);
        RotCube.SetMaterial(mat);

        RotCube.Init();

    }

    void Game::Update()
    {
        RotCube.Update();

    }

    void Game::Draw()
    {
        RotCube.Draw();
    }

} // namespace game
