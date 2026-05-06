#include "Renderer.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <spdlog/spdlog.h>
#include <stb_image.h>

#include "Camera.h"
#include "Colors.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Log.h"
#include "Window.h"

namespace basilisk
{
    void Renderer::InitGLFW()
    {
        Log::Get()->info("Loading GLFW");
        if (!glfwInit())
        {
            const char* description;
            int errorCode = glfwGetError(&description);

            Log::Get()->error("GLFW failed to initialize with error code {}.\n Error description: {}", errorCode, std::string(description));
            abort();
        }
        Log::Get()->info("GLFW loaded");
    }
    void Renderer::SetGlVersion()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void Renderer::InitGL() const
    {

        Log::Get()->info("Loading GLEW");
        if (const unsigned int errorCode = glewInit(); errorCode != GLEW_OK)
        {
            Log::Get()->error("GLEW failed to initialize with error code {}.\n Error description: {}", errorCode,
                              std::string(reinterpret_cast<const char*>(glewGetErrorString(errorCode))));
            abort();
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        stbi_set_flip_vertically_on_load(true);

        Log::Get()->info("GLEW loaded");
    }

    void Renderer::LoadProjectionMatrix()
    {
        const auto size = this->Window->GetSize();

        if (this->IsOrtho)
        {
            this->ProjectionMatrix = ortho(0.0f, static_cast<float>(size.x), 0.0f, static_cast<float>(size.y), 0.1f, 100.0f);
        }
        else
        {
            this->ProjectionMatrix = perspective(radians(45.0f), static_cast<float>(size.x) / static_cast<float>(size.y), 0.1f, 1000.0f);
        }
    }

    void Renderer::BindAndFillVbo(const unsigned int VboID, const int sizeArray, const float array[])
    {
        glBindBuffer(GL_ARRAY_BUFFER, VboID);
        glBufferData(GL_ARRAY_BUFFER, sizeArray, array, GL_STATIC_DRAW);
    }

    void Renderer::BindAndFillEbo(const unsigned int EboId, const int sizeArray, const unsigned int array[])
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeArray, array, GL_STATIC_DRAW);
    }

    void Renderer::SetAttribPointer(const int index, const int size, const int strideAmount, const int start)
    {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, strideAmount * static_cast<int>(sizeof(float)),
                              (void*)(start * sizeof(float)));
        glEnableVertexAttribArray(index);
    }

    void Renderer::BindBufferDataUV(const unsigned int vbo,
                                    const int amountVertices,
                                    float* arrayData,
                                    const int verticesBefore,
                                    const int sizeDataInVbo)
    {
        BindAndFillVbo(vbo, amountVertices, arrayData);
        SetAttribPointer(2, sizeDataInVbo, sizeDataInVbo + verticesBefore, verticesBefore);
    }

    void Renderer::GenerateVBs(Buffers& buffers, bool isTextured)
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

    void Renderer::Draw(const SPProc& shaderProg, unsigned int& vao, const int amountIndices) const
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
        this->ViewMatrix = lookAt(this->Cameras[this->ActiveCamera]->GetPosition(), this->Cameras[this->ActiveCamera]->GetTarget(),
                                  this->Cameras[this->ActiveCamera]->GetUp());
    }

    void Renderer::UpdateCameras() const
    {
        if (const auto& camera = this->Cameras[this->ActiveCamera]; camera)
        {
            camera->Update();
        }
    }

    Renderer& Renderer::GetInstance()
    {
        static Renderer instance;
        return instance;
    }

    mat4 Renderer::GetProjectionMatrix() const
    {
        return this->ProjectionMatrix;
    }

    mat4 Renderer::GetViewMatrix() const
    {
        return this->ViewMatrix;
    }


    void Renderer::SetWindowRef(basilisk::Window& window)
    {
        this->Window = &window;
    }

    void Renderer::SetCameraActive(const unsigned cameraId)
    {
        if (cameraId > Cameras.size())
        {
            Log::Get()->warn("Camera Id out of bounds.");
        }
        else
        {
            ActiveCamera = cameraId;
        }
    }

    void Renderer::AddCamera(const std::shared_ptr<Camera>& camera)
    {
        if (this->Cameras.capacity() <= this->Cameras.size())
        {
            this->Cameras.reserve(this->Cameras.size() + 10);
            this->Cameras.emplace_back(camera);
        }
        for (auto& spot : this->Cameras)
        {
            if (spot == nullptr)
            {
                spot = camera;
                return;
            }
        }
    }

    void Renderer::RemoveCamera(const std::shared_ptr<Camera>& camera)
    {
        for (auto& spot : this->Cameras)
        {
            if (spot == camera)
            {
                spot = nullptr;
                return;
            }
        }
    }

    void Renderer::RemoveCamera(const int cameraIndex)
    {
        this->Cameras[cameraIndex] = nullptr;
    }

    void Renderer::SetOrtho(bool isOrtho)
    {
        this->IsOrtho = isOrtho;
        this->LoadProjectionMatrix();
    }
} // basilisk
