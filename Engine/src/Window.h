#pragma once

#include <GLFW/glfw3.h>
#include <string>

#include "Export.h"

namespace basilisk
{
    class BASILISK_API Window
    {
    public:
        Window() = default;
        Window(const std::string& windowName, int sizeX, int sizeY);

        [[nodiscard]] GLFWwindow* GetWindow() const;
        bool WindowShouldClose() const;

    private:
        GLFWwindow* WindowP = nullptr;
        
    };

    class FailedWindowCreation : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Tried and failed creating a window";
        }
    };
} // basilisk 
