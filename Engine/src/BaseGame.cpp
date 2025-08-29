#include "BaseGame.h"

namespace basilisk
{
    BaseGame::BaseGame(const std::string& windowName, const math::Vec2<int> size)
    {
        this->Renderer = basilisk::Renderer();
        
        Renderer.InitGLFW();
        Renderer.InitGL();

        this->Window = basilisk::Window(windowName, size);


        Renderer.GenerateVBs();
    }



    void BaseGame::StartDraw() const
    {
        Renderer.StartDraw();
    }



    void BaseGame::Draw() const
    {
        Renderer.Draw();
    }



    void BaseGame::EndDraw() const
    {
        glfwSwapBuffers(this->Window.GetWindow());
        glfwPollEvents();
    }



    void BaseGame::Close() const
    {
        glfwTerminate();
    }
}
