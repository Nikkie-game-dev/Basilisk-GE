#pragma once

#include <exception>
#include <string>
#include "GL/glew.h"

namespace basilisk
{
    /// <summary>
    /// The Shader could not compile. Call What() for error message.
    /// </summary>
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
    
    /// <summary>
    /// The program could not compile. Call What() for error message.
    /// </summary>
    class ProgramCompileError : std::exception
    {
    public:
        using ShaderProc = unsigned int;

        explicit ProgramCompileError(const ShaderProc shader)
        {
            constexpr int infoBufferSize = 512;

            char infoLog[infoBufferSize];
            glGetProgramInfoLog(shader, infoBufferSize, nullptr, infoLog);

            Error = "Shader failed to compile: \n" + std::string(infoLog);
        }
        [[nodiscard]] char const* what() const override
        {
            return Error.c_str();
        }

    private:
        std::string Error;
    };

    /// <summary>
    /// GLFW Would not be initialized.
    /// </summary>
    class CouldNotStartGlfw : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Could not initialized GLFW";
        }
    };

    /// <summary>
    /// GLEW could not be initialized.
    /// </summary>
    class CouldNotStartGlew : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Could not initialized Glad";
        }
    };

    /// <summary>
    /// Material has not been assigned to an object that is trying to render.
    /// </summary>
    class MaterialUnassigned : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Material has not been assigned yet. Create a new one or reference shared_ptr.";
        }
    };
}
