#pragma once

#include "Export.h"

#include <string>

namespace basilisk
{
    class Window;
    class Renderer;

    class BASILISK_API BaseGame
    {
    public:
        BaseGame(const std::string& windowName, int sizeX, int sizeY);
        virtual ~BaseGame();
        
        BaseGame(const BaseGame& other); // copy constructor
        BaseGame(BaseGame&& other) noexcept; // move constructor
        BaseGame& operator=(const BaseGame& other); // copy assignment
        BaseGame& operator=(BaseGame&& other) noexcept; // move assignment

        void Run();

    protected:
        virtual void Draw() = 0;
        virtual void Init() = 0;
        virtual void Update() = 0;
        bool WindowShouldClose() const;
        void Close() const;
        Renderer& Renderer;

    private:
        std::string WindowName;
        int X;
        int Y;
        Window* Window;
    };

} // namespace basilisk
