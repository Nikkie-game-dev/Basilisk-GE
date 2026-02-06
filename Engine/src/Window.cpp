#include "Window.h"

#include <spdlog/spdlog.h>

#include "Loggers.h"
#include "Renderer.h"

namespace basilisk
{
    const std::shared_ptr<spdlog::logger> Window::Logger = spdlog::get(DEF_LOG);
    
    Window::Window(const char* windowName, const glm::ivec2 size) :
        Size(size)
    {
        /* Create a windowed mode window and its OpenGL context */
        this->WindowP = glfwCreateWindow(size.x, size.y, windowName, nullptr, nullptr);
        
        if (!this->WindowP)
        {
            glfwTerminate();
            spdlog::get(DEF_LOG)->error("Failed to create Window");
            spdlog::get(DEF_LOG)->flush();
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
