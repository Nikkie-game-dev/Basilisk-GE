#pragma once
#include "Export.h"
#include "glad/gl.h"

namespace basilisk
{
    BASILISK_API
    class Renderer
    {
    public:
        Renderer();
        void GenerateVBs() const;
        void Draw() const;
        void StartDraw() const;
    private:
        using BufferProc = unsigned int;
        using ShaderProc = unsigned int;
        using SPProc = unsigned int;
        BufferProc* Vbo;
        BufferProc* Vao;
        SPProc ShaderProg;
        void PopulateVbo() const;
        void UpdateVertexAttributes() const;
        void BindVertexBuffer() const;
        void BindVertexBuffer(BufferProc vao) const;
        void GenerateVAO() const;
        void GenerateVBO() const;
        void CompileShaders();
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
} // basilisk
