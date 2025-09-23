#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>

#include "Export.h"

namespace basilisk
{
    class BASILISK_API Window
    {
    public:
        Window() = default;
        Window(const std::string& windowName, glm::ivec2 size);

        [[nodiscard]] GLFWwindow* GetWindow() const;
        [[nodiscard]] bool WindowShouldClose() const;
        [[nodiscard]] glm::ivec2 GetSize() const;
    
    private:
        GLFWwindow* WindowP = nullptr;
        glm::ivec2 Size;
        
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
