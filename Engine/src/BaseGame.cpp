#include "BaseGame.h"
#include <glm/glm.hpp>
#include "Renderer.h"
#include "Window.h"

namespace basilisk
{

    BaseGame::BaseGame(const std::string& windowName, int sizeX, int sizeY) : X(sizeX), Y(sizeY), Renderer(Renderer::GetInstance())
    {
        Renderer.InitGLFW();

        Renderer.SetGlVersion();

        this->Window = new basilisk::Window(windowName, glm::vec2(sizeX, sizeY));

        Renderer.InitGL();

    }

    BaseGame::~BaseGame()
    {
        delete this->Window;
    }

    BaseGame::BaseGame(const BaseGame& other) : X(other.X), Y(other.Y), Renderer(Renderer::GetInstance())
    {
        this->WindowName = other.WindowName;
        this->Window = new basilisk::Window(other.WindowName, glm::vec2(other.X, other.Y));
    }

    BaseGame::BaseGame(BaseGame&& other) noexcept : X(other.X), Y(other.Y), Renderer(Renderer::GetInstance())
    {
        this->WindowName = other.WindowName;
        this->Window = other.Window;
        other.Window = nullptr;
        other.X = 0;
        other.Y = 0;
        other.WindowName = "";
    }

    BaseGame& BaseGame::operator=(const BaseGame& other)
    {
        if (this != &other)
        {
            this->X = other.X;
            this->Y = other.Y;
            this->WindowName = other.WindowName;
            this->Window = new basilisk::Window(other.WindowName, glm::vec2(other.X, other.Y));
        }
        return *this;
    }

    BaseGame& BaseGame::operator=(BaseGame&& other) noexcept
    {
        if (this != &other)
        {
            this->X = other.X;
            this->Y = other.Y;
            this->WindowName = other.WindowName;
            this->Window = other.Window;

            other.Window = nullptr;
            other.X = 0;
            other.Y = 0;
            other.WindowName = "";
        }
        return *this;
    }

    void BaseGame::Run()
    {
        Init();

        while (!WindowShouldClose())
        {
            Update();
            Renderer.StartDraw();
            Draw();
            Renderer.EndDraw();
        }

        Close();
    }

    void BaseGame::Draw()
    {
        //Renderer.Draw();
    }

    void BaseGame::Init()
    {
    }

    bool BaseGame::WindowShouldClose() const
    {
        return Window->WindowShouldClose();
    }

    void BaseGame::Close() const
    {
        glfwTerminate();
    }
} // namespace basilisk
