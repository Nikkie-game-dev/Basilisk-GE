#include "Window.h"

namespace basilisk
{
    Window::Window(const std::string& windowName, const math::Vec2<int> size)
    {
        /* Create a windowed mode window and its OpenGL context */
        this->WindowP = glfwCreateWindow(size.X, size.Y, windowName.c_str(), nullptr, nullptr);
        if (!WindowP)
        {
            glfwTerminate();
            throw FailedWindowCreation();
        }
    }



    GLFWwindow* Window::GetWindow() const
    {
        return WindowP;
    }
}