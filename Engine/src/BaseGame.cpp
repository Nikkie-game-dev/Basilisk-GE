#include "BaseGame.h"

#include "glad/gl.h"

namespace basilisk
{

    BaseGame::BaseGame(const std::string& windowName, const math::Vec2<int> size)
    {
        if (!glfwInit())
        {
            throw CouldNotStartGlfw();
        }

        this->Window = basilisk::Window(windowName, size);

        if (!gladLoadGL(glfwGetProcAddress))
        {
            throw CouldNotStartGlad();
        }

        // Generate VAO
        glGenVertexArrays(1, &this->Vao);
        glBindVertexArray(this->Vao);

        //Generate VBO
        glGenBuffers(1, &this->Vbo);
        glBindBuffer(GL_ARRAY_BUFFER, this->Vbo);

        PopulateVbo();

    }
}
