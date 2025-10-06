#include "BaseGame.h"

#include <chrono>
#include <glm/glm.hpp>
#include <iostream>

#include "Renderer.h"
#include "Window.h"

namespace basilisk
{

    BaseGame::BaseGame(const std::string& windowName, const int sizeX, const int sizeY) :
        Renderer(Renderer::GetInstance()), X(sizeX), Y(sizeY)
    {
        try
        {
            Renderer.InitGLFW();

            Renderer.SetGlVersion();

            this->Window = new basilisk::Window(windowName, glm::ivec2(sizeX, sizeY));

            Renderer.InitGL();

            Renderer.SetWindowRef(*this->Window);
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
            Init();
            auto old = std::chrono::system_clock::now();
            
            while (!WindowShouldClose())
            {
                auto now = std::chrono::system_clock::now();
                
                Delta = std::chrono::duration<float>(now - old).count();
                
                Update();
                Renderer.StartDraw();
                Draw();
                Renderer.EndDraw();
                
                old = std::chrono::system_clock::now();
            }

            Close();
        }
        catch (std::exception& error)
        {
            std::cerr << error.what();
        }
    }

    bool BaseGame::WindowShouldClose() const
    {
        return Window->WindowShouldClose();
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
