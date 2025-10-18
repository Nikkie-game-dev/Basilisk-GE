#include "Material.h"

#include <GL/glew.h>
#include <iostream>

#include "RenderException.h"
#include "glm/gtc/type_ptr.hpp"

namespace basilisk
{
    using ShaderProc = unsigned int;

    Material::Material(const bool isTextured) :
        IsTextured(isTextured)
    {
    }

    std::shared_ptr<Material> Material::New(const bool isSolid)
    {
        // Makes a new object with a shared pointer.
        return std::make_shared<Material>(isSolid);
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
            std::cerr <<  ShaderCompileError(vertexShader).what() << std::endl;
        }

        glShaderSource(fragmentShader, 1, this->IsTextured ? &FragShaderTextureless : &FragShader, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            std::cerr <<  ShaderCompileError(fragmentShader).what() << std::endl;
        }

        /*Shader program attachment and linking*/
        glAttachShader(this->ShaderProgram, vertexShader);
        glAttachShader(this->ShaderProgram, fragmentShader);
        glLinkProgram(this->ShaderProgram);

        glGetProgramiv(this->ShaderProgram, GL_LINK_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            std::cerr <<  ShaderCompileError(this->ShaderProgram).what() << std::endl;
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
        "in vec2 TexCoord;\n"
    
        "uniform sampler2D OutTexture;\n"
    
        "void main()\n"
        "{\n"
        " FragColor = OutColor;\n"
        "}\n";
    
    const char* Material::FragShaderTextureless = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 OutColor;\n"
    
        "void main()\n"
        "{\n"
        " FragColor = OutColor;\n"
        "}\n";
} // namespace basilisk
