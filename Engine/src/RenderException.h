#pragma once

#include <exception>
#include <string>
#include "GL/glew.h"

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

class CouldNotStartGlfw : std::exception
{
public:
    [[nodiscard]] char const* what() const override
    {
        return "Could not initialized GLFW";
    }
};


class CouldNotStartGlew : std::exception
{
public:
    [[nodiscard]] char const* what() const override
    {
        return "Could not initialized Glad";
    }
};


class MaterialUnassigned : std::exception
{
public:
    [[nodiscard]] char const* what() const override
    {
        return "Material has not been assigned yet. Create a new one or reference shared_ptr.";
    }
};
