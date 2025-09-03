#include "BaseGame.h"

namespace basilisk
{
    BaseGame::BaseGame(const std::string& windowName, const math::Vec2<int> size)
    {
        auto& renderInstance = Renderer::GetInstance();
        
        renderInstance.InitGLFW();
        renderInstance.InitGL();

        this->Window = basilisk::Window(windowName, size);


        renderInstance.GenerateVBs();
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
