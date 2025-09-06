#pragma once

#include <exception>
#include <string>

#include "Export.h"
#include "GL/glew.h"

namespace basilisk
{

    using BufferProc = unsigned int;
    using ShaderProc = unsigned int;
    using SPProc = unsigned int;

    class BASILISK_API Renderer
    {
    public:
        void InitGLFW();
        void SetGlVersion();
        void InitGL() const;
        void GenerateVBs();
        void Draw() const;
        void StartDraw() const;
        void EndDraw() const;
        static Renderer& GetInstance();

        Renderer(const Renderer& other) = delete;            // copy constructor
        Renderer(Renderer&& other) = delete;                 // move constructor
        Renderer& operator=(const Renderer& other) = delete; // copy assignment
        Renderer& operator=(Renderer&& other) = delete;      // move assignment
        
    private:
        Renderer() = default;
        ~Renderer() = default;
        BufferProc Vbo;
        BufferProc Vao;
        BufferProc Ebo;
        SPProc ShaderProg;

        void PopulateVBO() const;
        void PopulateEBO() const;
        void UpdateVertexAttributes() const;
        void UnbindVertexArray() const;
        void BindVertexArray() const;
        void GenerateVAO();
        void GenerateVBO();
        void GenerateEBO();
        void BuildShaders();
    };

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
} // namespace basilisk
