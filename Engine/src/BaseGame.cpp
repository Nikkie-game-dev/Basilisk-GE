#include "BaseGame.h"
#include "Renderer.h"
#include "Window.h"

namespace basilisk
{

    BaseGame::BaseGame(const std::string& windowName, int sizeX, int sizeY) :
        Renderer(Renderer::GetInstance())
    {
        Renderer.InitGLFW();

        Renderer.SetGlVersion();

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
