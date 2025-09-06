#include "BaseGame.h"
#include "Renderer.h"
#include "Window.h"

namespace basilisk
{

    BaseGame::BaseGame(const std::string& windowName, int sizeX, int sizeY)
    {
        auto& renderInstance = Renderer::GetInstance();
        
        renderInstance.InitGLFW();
        renderInstance.InitGL();

        Window = new basilisk::Window(windowName, sizeX, sizeY);


        renderInstance.GenerateVBs();
    }

    BaseGame::~BaseGame()
    {
        delete Window;
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
