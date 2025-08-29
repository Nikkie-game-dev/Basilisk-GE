#pragma once
#define GLFW_INCLUDE_NONE

#include <glad/gl.h>
#include <exception>

#include "Export.h"
#include "Window.h"
#include "Renderer.h"

namespace basilisk
{
    BASILISK_API
    class BaseGame
    {
    public:
        BaseGame(const std::string& windowName, math::Vec2<int> size);

        void StartDraw() const;
        void Draw() const;
        void EndDraw() const;
        void Close() const;

    private:
        Window Window;
        Renderer Renderer;
    };


    BASILISK_API
    class CouldNotStartGlfw : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Could not initialized GLFW";
        }
    };


    BASILISK_API
    class CouldNotStartGlad : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Could not initialized Glad";
        }
    };
    
} // basilisk 
