#include "BaseGame.h"
#include "Renderer.h"
#include "Window.h"

namespace basilisk
{
    static Window* window;

    BaseGame::BaseGame(const std::string& windowName, int sizeX, int sizeY)
    {
        auto& renderInstance = Renderer::GetInstance();
        
        renderInstance.InitGLFW();
        renderInstance.InitGL();

        window = new Window(windowName, sizeX, sizeY);


        renderInstance.GenerateVBs();
    }

    BaseGame::~BaseGame()
    {
        delete window;
    }

    void BaseGame::Draw() const
    {
        Renderer::GetInstance().Draw();
    }

    void BaseGame::Close() const
    {
        glfwTerminate();
    }
}
