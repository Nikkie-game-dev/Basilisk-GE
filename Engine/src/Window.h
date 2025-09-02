#pragma once

#include <GLFW/glfw3.h>
#include <string>

#include "Export.h"
#include "math/Vec2.h"

namespace basilisk
{
    BASILISK_API
    class Window
    {
    public:
        Window() = default;
        Window(const std::string& windowName, math::Vec2<int> size);

        [[nodiscard]] GLFWwindow* GetWindow() const;

    private:
        GLFWwindow* WindowP = nullptr;
        
    };

    BASILISK_API
    class FailedWindowCreation : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Tried and failed creating a window";
        }
    };
} // basilisk 
