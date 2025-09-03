#pragma once


#include "Export.h"
#include "Window.h"
#include "Renderer.h"

namespace basilisk
{
    class BASILISK_API BaseGame
    {
    public:
        BaseGame(const std::string& windowName, math::Vec2<int> size);
        void Draw() const;
        void Close() const;

    private:
        Window Window;
    };
    
} // basilisk 
