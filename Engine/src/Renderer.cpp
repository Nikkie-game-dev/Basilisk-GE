#include "Renderer.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Colors.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "RenderException.h"
#include "Window.h"

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

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::LoadProjectionMatrix()
    {
        const auto size = this->Window->GetSize();
        this->ProjectionMatrix = glm::ortho(0.0f, static_cast<float>(size.x), 0.0f, static_cast<float>(size.y), 0.1f, 100.0f);
    }

    void Renderer::BindAndFillVbo(unsigned int VboID, int sizeArray, float array[])
    {
        glBindBuffer(GL_ARRAY_BUFFER, VboID);
        glBufferData(GL_ARRAY_BUFFER, sizeArray, array, GL_STATIC_DRAW);
    }

    void Renderer::BindAndFillEbo(unsigned int EboId, int sizeArray, unsigned int array[])
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeArray, array, GL_STATIC_DRAW);
    }

    void Renderer::SetAttribPointer(const int index, const int size, const int strideAmount, const int start)
    {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, strideAmount * static_cast<int>(sizeof(float)), (void*)(start * sizeof(float)));
        glEnableVertexAttribArray(index);
    }

    void Renderer::GenerateVBs(Buffers& buffers, const bool isTextured)
    {
        constexpr int posSize = 3;
        const int textureSize = isTextured ? 2 : 0;
        const int stride = posSize + Color::ColorParamsAmount + textureSize;

        glGenVertexArrays(1, &buffers.Vao);
        glBindVertexArray(buffers.Vao);

        glGenBuffers(1, &buffers.Vbo);
        glGenBuffers(1, &buffers.Ebo);

        BindAndFillVbo(buffers.Vbo, buffers.AmountVertices, buffers.Vertices);
        BindAndFillEbo(buffers.Ebo, buffers.AmountIndices, buffers.Indices);

        //Position
        SetAttribPointer(0, posSize, stride, 0);

        //Color
        SetAttribPointer(1, Color::ColorParamsAmount, stride, posSize);

        if (isTextured)
        {
            SetAttribPointer(2, textureSize, stride, posSize + Color::ColorParamsAmount);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Renderer::Draw(const SPProc shaderProg, unsigned int& vao, const int amountIndices) const
    {
        glUseProgram(shaderProg);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, amountIndices, GL_UNSIGNED_INT, nullptr);
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

    void Renderer::UpdateViewMatrix()
    {
        this->ViewMatrix = glm::lookAt(this->CameraPos, this->CameraTarget, this->CameraUp);
    }

    Renderer& Renderer::GetInstance()
    {
        static Renderer instance;
        return instance;
    }

    glm::vec3 Renderer::GetCameraUp() const
    {
        return this->CameraUp;
    }


    glm::vec3 Renderer::GetCameraTarget() const
    {
        return this->CameraTarget;
    }

    glm::vec3 Renderer::GetCameraPos() const
    {
        return this->CameraPos;
    }

    glm::mat4 Renderer::GetProjectionMatrix() const
    {
        return this->ProjectionMatrix;
    }

    glm::mat4 Renderer::GetViewMatrix() const
    {
        return this->ViewMatrix;
    }


    void Renderer::SetWindowRef(basilisk::Window& window)
    {
        this->Window = &window;
    }

    Renderer::Renderer() :
        CameraPos(0, 0, 3.0f),
        CameraTarget(0, 0, 0),
        Window(nullptr)
    {
        const auto invDirection = glm::normalize(CameraPos - CameraTarget);
        const auto right = glm::normalize(glm::cross(glm::vec3(0, 1.0, 0), invDirection));
        this->CameraUp = glm::cross(invDirection, right);
    }


#pragma region deprecated
    void Renderer::Draw(const SPProc shaderProg, unsigned int& vao, const int amountIndices, const Color color) const
    {
        const int vertexColorLocation = glGetUniformLocation(shaderProg, "SolidColor");
        glUseProgram(shaderProg);
        glUniform4f(vertexColorLocation,
                    static_cast<float>(color.R) / static_cast<float>(Color::MaxValue),
                    static_cast<float>(color.G) / static_cast<float>(Color::MaxValue),
                    static_cast<float>(color.B) / static_cast<float>(Color::MaxValue),
                    color.A);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, amountIndices, GL_UNSIGNED_INT, nullptr);
    }
#pragma endregion
} // basilisk
