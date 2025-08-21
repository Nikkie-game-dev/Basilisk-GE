#pragma once
#define GLFW_INCLUDE_NONE

#include "Export.h"

#include "Window.h"

namespace basilisk
{
    using BufferProc = unsigned int;
    using VsoProc = unsigned int;
    using SPProc = unsigned int;


    BASILISK_API
    class BaseGame
    {
    public:
        BaseGame(const std::string& windowName, math::Vec2<int> size);

        void StartDraw();
        void Draw();
        void EndDraw();
        void Close();

    private:
        Window Window;
        BufferProc Vbo;
        BufferProc Vao;
    };
} // basilisk 
