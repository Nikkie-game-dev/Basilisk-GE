#include "Renderer.h"

#include "Colors.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "RenderException.h"

namespace basilisk
{
    void Renderer::InitGLFW()
    {
        if (!glfwInit())
        {
            throw CouldNotStartGlfw();
        }
    }
    void Renderer::SetGlVersion()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void Renderer::InitGL() const
    {
        if (glewInit() != GLEW_OK)
        {
            throw CouldNotStartGlew();
        }
    }

    void Renderer::StartDraw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::EndDraw() const
    {
        glfwSwapBuffers(glfwGetCurrentContext());
        glfwPollEvents();
    }

    Renderer& Renderer::GetInstance()
    {
        static Renderer instance;
        return instance;
    }

    void Renderer::GenerateVBs(float vertices[], unsigned int indices[], const int amountVertices, const int amountIndices)
    {
        glGenVertexArrays(1, &this->Vao);
        glBindVertexArray(this->Vao);

        glGenBuffers(1, &this->Vbo);
        glGenBuffers(1, &this->Ebo);

        glBindBuffer(GL_ARRAY_BUFFER, this->Vbo);
        glBufferData(GL_ARRAY_BUFFER, amountVertices, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->Ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, amountIndices, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));

        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    

    void Renderer::Draw(SPProc ShaderProg) const
    {
        glUseProgram(ShaderProg);
        glBindVertexArray(this->Vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::Draw(const SPProc shaderProg, const Color color) const
    {
        const int vertexColorLocation = glGetUniformLocation(shaderProg, "SolidColor");
        glUseProgram(shaderProg);
        glUniform4f(vertexColorLocation,
                    static_cast<float>(color.R) / static_cast<float>(Color::MaxValue),
                    static_cast<float>(color.G) / static_cast<float>(Color::MaxValue),
                    static_cast<float>(color.B) / static_cast<float>(Color::MaxValue),
                    color.A);
        glBindVertexArray(this->Vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
    
} // namespace basilisk
