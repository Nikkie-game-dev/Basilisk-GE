#pragma once
#define GLFW_INCLUDE_NONE

#include "Export.h"

#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <exception>
#include <string>

namespace basilisk
{
    BASILISK_API
    class Renderer
    {
    public:
        Renderer();
        void InitGLFW();
        void InitGL() const;
        void GenerateVBs();
        void Draw() const;
        void StartDraw() const;
        void EndDraw() const;

    private:
        using BufferProc = unsigned int;
        using ShaderProc = unsigned int;
        using SPProc = unsigned int;
        BufferProc Vbo;
        BufferProc Vao;
        SPProc ShaderProg;
        void PopulateVBO() const;
        void UpdateVertexAttributes() const;
        void BindVertexBuffer() const;
        void BindVertexBuffer(BufferProc vao) const;
        void GenerateVAO();
        void GenerateVBO();
        void BuildShaders();
    };

    BASILISK_API
    class ShaderCompileError : std::exception
    {
    public:
        using ShaderProc = unsigned int;

        explicit ShaderCompileError(const ShaderProc shader)
        {
            constexpr int infoBufferSize = 512;

            char infoLog[infoBufferSize];
            glGetShaderInfoLog(shader, infoBufferSize, nullptr, infoLog);

            Error = "Shader failed to compile: \n" + std::string(infoLog);
        }
        [[nodiscard]] char const* what() const override
        {
            return Error.c_str();
        }

    private:
        std::string Error;
    };

    BASILISK_API
    class CouldNotStartGlfw : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Could not initialized GLFW";
        }
    };


    BASILISK_API
    class CouldNotStartGlad : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Could not initialized Glad";
        }
    };
} // namespace basilisk
