#include "Window.h"

namespace basilisk
{
    Window::Window(const std::string& windowName, glm::vec2 size)
    {
        /* Create a windowed mode window and its OpenGL context */
        this->WindowP = glfwCreateWindow(size.x, size.y, windowName.c_str(), nullptr, nullptr);
        if (!this->WindowP)
        {
            glfwTerminate();
            throw FailedWindowCreation();
        }
        glfwMakeContextCurrent(this->WindowP);

    }

    GLFWwindow* Window::GetWindow() const
    {
        return this->WindowP;
    }
    
    bool Window::WindowShouldClose() const
    {
        return glfwWindowShouldClose(this->WindowP);
    }
}
