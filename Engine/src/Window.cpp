#include "Window.h"

#include "Log.h"
#include "Renderer.h"

namespace basilisk
{
    
    Window::Window(const char* windowName, const glm::ivec2& size) :
        Size(size)
    {
        Log::Get()->info("Creating window");
        
        /* Create a windowed mode window and its OpenGL context */
        this->WindowP = glfwCreateWindow(size.x, size.y, windowName, nullptr, nullptr);
        
        if (!this->WindowP)
        {
            glfwTerminate();
            Log::Get()->error("Failed to create Window");
            abort();
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
    glm::ivec2 Window::GetSize() const
    {
        return this->Size;
    }
}
