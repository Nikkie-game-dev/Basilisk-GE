#include "BaseGame.h"

#include <chrono>
#include <glm/glm.hpp>
#include <iostream>

#include "Renderer.h"
#include "Window.h"

namespace basilisk
{

    BaseGame::BaseGame(const char* windowName, const int sizeX, const int sizeY) :
        Renderer(Renderer::GetInstance()), X(sizeX), Y(sizeY)
    {
        try
        {

            this->Renderer.InitGLFW();

            this->Renderer.SetGlVersion();

            this->Window = new basilisk::Window(windowName, glm::ivec2(sizeX, sizeY));
            
            this->WindowName = windowName;

            this->Renderer.InitGL();

            Renderer.SetWindowRef(*this->Window);
            this->Renderer.SetWindowRef(*this->Window);
        }
        catch (std::exception& error)
        {
            std::cerr << error.what();
        }
    }

    BaseGame::~BaseGame()
    {
        delete this->Window;
    }

    BaseGame::BaseGame(const BaseGame& other) :
        Renderer(Renderer::GetInstance()), X(other.X), Y(other.Y)
    {
        try
        {
            this->WindowName = other.WindowName;
            this->Window = new basilisk::Window(other.WindowName, glm::vec2(other.X, other.Y));
            Renderer.SetWindowRef(*this->Window);
            this->Renderer.SetWindowRef(*this->Window);
        }
        catch (std::exception& error)
        {
            std::cerr << error.what();
        }
    }

    BaseGame::BaseGame(BaseGame&& other) noexcept :
        Renderer(Renderer::GetInstance()), X(other.X), Y(other.Y)
    {
        try
        {
            this->WindowName = other.WindowName;
            this->Window = other.Window;
            other.Window = nullptr;
            other.X = 0;
            other.Y = 0;
            other.WindowName = "";
            Renderer.SetWindowRef(*this->Window);
            this->Renderer.SetWindowRef(*this->Window);
        }
        catch (std::exception& error)
        {
            std::cerr << error.what();
        }
    }

    BaseGame& BaseGame::operator=(const BaseGame& other)
    {
        try
        {
            if (this != &other)
            {
                this->X = other.X;
                this->Y = other.Y;
                this->WindowName = other.WindowName;
                this->Window = new basilisk::Window(other.WindowName, glm::vec2(other.X, other.Y));
                Renderer.SetWindowRef(*this->Window);
                this->InputSystem = Input(this->Window);
            }
        }
        catch (std::exception& error)
        {
            std::cerr << error.what();
        }

        return *this;

    }

    BaseGame& BaseGame::operator=(BaseGame&& other) noexcept
    {
        try
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

                Renderer.SetWindowRef(*this->Window);
                this->InputSystem = Input(this->Window);
            }
        }
        catch (std::exception& error)
        {
            std::cerr << error.what();
        }
        return *this;
    }

    void BaseGame::Run()
    {
        try
        {
            this->Init();
            auto old = std::chrono::system_clock::now();
            std::chrono::time_point<std::chrono::system_clock> now = old;

            while (!this->WindowShouldClose())
            {

                this->Delta = std::chrono::duration<float>(now - old).count();
                old = std::chrono::system_clock::now();

                this->Update();
                this->Renderer.StartDraw();
                this->Draw();
                this->Renderer.EndDraw();

                now = std::chrono::system_clock::now();
            }

            this->Close();
        }
        catch (std::exception& error)
        {
            std::cerr << error.what();
        }
    }

    bool BaseGame::WindowShouldClose() const
    {
        return this->Window->WindowShouldClose();
    }

    void BaseGame::Close() const
    {
        glfwTerminate();
    }

    float BaseGame::GetDelta()
    {
        return this->Delta;
    }
} // namespace basilisk
