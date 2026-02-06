#include "Material.h"

#include <GL/glew.h>
#include <spdlog/spdlog.h>

#include "Loggers.h"
#include "glm/gtc/type_ptr.hpp"

namespace basilisk
{
    using ShaderProc = unsigned int;

    const std::shared_ptr<spdlog::logger> Material::Logger = spdlog::get(DEF_LOG);


    Material::Material(const bool isTextured) :
        IsTextured(isTextured)
    {
    }

    std::shared_ptr<Material> Material::New(const bool isTextured)
    {
        // Makes a new object with a shared pointer.
        return std::make_shared<Material>(isTextured);
    }

    void Material::BuildShader()
    {

        const ShaderProc vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const ShaderProc fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        this->ShaderProgram = glCreateProgram();

        GLint hasCompiled;

        glShaderSource(vertexShader, 1, &VertexShader, nullptr);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            ShaderCompileError(vertexShader);
        }

        glShaderSource(fragmentShader, 1, this->IsTextured ? &FragShader : &FragShaderTextureless, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            ShaderCompileError(fragmentShader);
        }

        /*Shader program attachment and linking*/
        glAttachShader(this->ShaderProgram, vertexShader);
        glAttachShader(this->ShaderProgram, fragmentShader);
        glLinkProgram(this->ShaderProgram);

        glGetProgramiv(this->ShaderProgram, GL_LINK_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            ShaderCompileError(fragmentShader);

            ProgramCompileError(this->ShaderProgram);
        }

        /*Deletion*/
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }

    SPProc Material::GetShaderProgram() const
    {
        return this->ShaderProgram;
    }

    bool Material::GetIsTextured() const
    {
        return IsTextured;
    }

    void Material::UpdateGLMatrix(glm::mat4 matrix, const std::string& name) const
    {
        glUseProgram(this->ShaderProgram);

        const GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str());

        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Material::ShaderCompileError(const ShaderProc shader)
    {
        constexpr int infoBufferSize = 512;

        char infoLog[infoBufferSize];
        glGetShaderInfoLog(shader, infoBufferSize, nullptr, infoLog);
        Logger->error("Shader failed to compile:\n{}", std::string(infoLog));
        Logger->flush();
        abort();
    }

    void Material::ProgramCompileError(SPProc program)
    {
        constexpr int infoBufferSize = 512;

        char infoLog[infoBufferSize];
        glGetProgramInfoLog(program, infoBufferSize, nullptr, infoLog);
        Logger->error("Shader program failed to compile:\n{}", std::string(infoLog));
        Logger->flush();
        abort();
    }

    const char* Material::VertexShader = "#version 330 core\n"
        "layout (location = 0) in vec3 Pos;\n"
        "layout (location = 1) in vec4 Color;\n"
        "layout (location = 2) in vec2 TexCoord;\n"

        "out vec4 OutColor;\n"
        "out vec2 OutTexCoord;\n"

        "uniform mat4 matrix;\n"

        "void main()\n"
        "{\n"
        " gl_Position = matrix * vec4(Pos, 1.0);\n"
        " OutColor = Color;\n"
        " OutTexCoord = TexCoord;\n"
        "}\0";

    const char* Material::FragShader = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 OutColor;\n"
        "in vec2 OutTexCoord;\n"

        "uniform sampler2D OutTexture;\n"

        "void main()\n"
        "{\n"
        " FragColor = texture(OutTexture, OutTexCoord) * OutColor;\n"
        "}\n";

    const char* Material::FragShaderTextureless = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 OutColor;\n"

        "void main()\n"
        "{\n"
        " FragColor = OutColor;\n"
        "}\n";
} // namespace basilisk
