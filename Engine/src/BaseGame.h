#pragma once
#define GLFW_INCLUDE_NONE

#include <glad/gl.h>
#include <exception>

#include "Export.h"
#include "Window.h"

namespace basilisk
{
    using BufferProc = unsigned int;
    using ShaderProc = unsigned int;
    using SPProc = unsigned int;


    BASILISK_API
    class BaseGame
    {
    public:
        BaseGame(const std::string& windowName, math::Vec2<int> size);

        void StartDraw() const;
        void Draw() const;
        void EndDraw() const;
        void Close() const;

    private:
        void PopulateVbo();
        void CompileShaders();

        Window Window;
        BufferProc Vbo;
        BufferProc Vao;
        SPProc ShaderProg;
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


    BASILISK_API
    class ShaderCompileError : std::exception
    {
    public:
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
