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
        Window(const char* windowName, glm::ivec2 size);

        /// <summary>
        /// Getter for the window pointer
        /// </summary>
        /// <returns>The window pointer</returns>
        [[nodiscard]] GLFWwindow* GetWindow() const;
        /// <summary>
        /// Checks if the window should close given the current conditions.
        /// </summary>
        /// <returns>True if it should close, false if it should not</returns>
        [[nodiscard]] bool WindowShouldClose() const;
        /// <summary>
        /// Getter for the size of the window
        /// </summary>
        /// <returns>The size of the window (x = width, y = height)</returns>
        [[nodiscard]] glm::ivec2 GetSize() const;
    
    private:
        GLFWwindow* WindowP = nullptr;
        glm::ivec2 Size;
        
    };

    /// <summary>
    /// Window could not be created.
    /// </summary>
    class FailedWindowCreation : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Tried and failed creating a window";
        }
    };
} // basilisk 
