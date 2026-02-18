#include "BaseGame.h"

#include <chrono>
#include <glm/glm.hpp>
#include <iostream>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

#include "Loggers.h"

#include "Renderer.h"
#include "Window.h"

#define MAX_LOGS 3
#define MAX_LOG_SIZE (1024 * 1024)

namespace basilisk
{

    void BaseGame::SetUpLog()
    {
        const auto console = std::make_shared<spdlog::sinks::wincolor_stderr_sink_st>();
        const auto errorDump = std::make_shared<spdlog::sinks::rotating_file_sink_st>("logs/dump.log", MAX_LOG_SIZE, MAX_LOGS);
        std::vector<spdlog::sink_ptr> sinks{console, errorDump};

        Logger = std::make_shared<spdlog::logger>(DEF_LOG, sinks.begin(), sinks.end());
        spdlog::register_logger(Logger);
    }

    BaseGame::BaseGame(const char* windowName, const int sizeX, const int sizeY) :
        Renderer(Renderer::GetInstance()), X(sizeX), Y(sizeY), InputSystem(nullptr)
    {

        SetUpLog();

        this->Renderer.InitGLFW();

        this->Renderer.SetGlVersion();

        this->Window = new basilisk::Window(windowName, glm::ivec2(sizeX, sizeY));

        this->WindowName = windowName;

        this->Renderer.InitGL();

        this->Renderer.SetWindowRef(*this->Window);

        this->InputSystem = Input(this->Window);

    }

    BaseGame::~BaseGame()
    {
        delete this->Window;
    }

    BaseGame::BaseGame(const BaseGame& other) :
        Renderer(Renderer::GetInstance()), X(other.X), Y(other.Y), InputSystem(nullptr)
    {

        this->WindowName = other.WindowName;
        this->Window = new basilisk::Window(other.WindowName, glm::vec2(other.X, other.Y));
        this->Renderer.SetWindowRef(*this->Window);
        this->InputSystem = Input(this->Window);

    }

    BaseGame::BaseGame(BaseGame&& other) noexcept :
        Renderer(Renderer::GetInstance()), X(other.X), Y(other.Y), InputSystem(nullptr)
    {

        this->WindowName = other.WindowName;
        this->Window = other.Window;
        other.Window = nullptr;
        other.X = 0;
        other.Y = 0;
        other.WindowName = "";
        this->Renderer.SetWindowRef(*this->Window);
        this->InputSystem = Input(this->Window);

    }

    BaseGame& BaseGame::operator=(const BaseGame& other)
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

            Renderer.SetWindowRef(*this->Window);
            this->InputSystem = Input(this->Window);
        }

        return *this;
    }

    void BaseGame::Run()
    {
        this->Init();
        auto old = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> now = old;

        while (!this->WindowShouldClose())
        {
            this->InputSystem.UpdateInputs();

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

    Input& BaseGame::GetInputSystem()
    {
        return this->InputSystem;
    }
} // namespace basilisk
