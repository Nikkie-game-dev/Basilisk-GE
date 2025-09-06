#include "BaseGame.h"
#include "Renderer.h"
#include "Window.h"

namespace basilisk
{

    BaseGame::BaseGame(const std::string& windowName, int sizeX, int sizeY) :
        X(sizeX), Y(sizeY)
    {
        auto& renderInstance = Renderer::GetInstance();

        renderInstance.InitGLFW();
        renderInstance.InitGL();

        this->Window = new basilisk::Window(windowName, sizeX, sizeY);


        renderInstance.GenerateVBs();
    }

    BaseGame::~BaseGame()
    {
        delete this->Window;
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
