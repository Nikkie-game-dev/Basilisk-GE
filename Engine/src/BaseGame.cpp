#include "BaseGame.h"
#include "Renderer.h"
#include "Window.h"

namespace basilisk
{

    BaseGame::BaseGame(const std::string& windowName, int sizeX, int sizeY) :
        Renderer(Renderer::GetInstance())
    {
        Renderer.InitGLFW();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        this->Window = new basilisk::Window(windowName, sizeX, sizeY);
        
        Renderer.InitGL();


        Renderer.GenerateVBs();
    }

    BaseGame::~BaseGame()
    {
        delete this->Window;
    }

    void BaseGame::Draw()
    {
        Renderer.Draw();
    }

    void BaseGame::Close() const
    {
        glfwTerminate();
    }
}
