#include "BaseGame.h"

namespace basilisk
{

    BaseGame::BaseGame(const std::string& windowName, const math::Vec2<int> size)
    {
        if (!glfwInit())
        {
            throw CouldNotStartGlfw();
        }

        this->Window = basilisk::Window(windowName, size);
        this->Renderer = basilisk::Renderer();


        if (!gladLoadGL(glfwGetProcAddress))
        {
            throw CouldNotStartGlad();
        }

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
