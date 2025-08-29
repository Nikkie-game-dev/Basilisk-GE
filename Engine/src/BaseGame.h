#pragma once

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
        void Draw() const;
        void Close() const;

    private:
        Window Window;
        Renderer Renderer;
    };
    
} // basilisk 
