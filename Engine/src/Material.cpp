#include "Material.h"

#include <GL/glew.h>

#include "RenderException.h"
#include "glm/gtc/type_ptr.hpp"

namespace basilisk
{
    using ShaderProc = unsigned int;

    Material::Material(const bool isSolid) :
        IsSolid(isSolid)
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

        glShaderSource(vertexShader, 1, this->IsSolid ? &VertexShaderSolid : &VertexShaderNotSolid, nullptr);

        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            throw ShaderCompileError(vertexShader);
        }

        glShaderSource(fragmentShader, 1, this->IsSolid ? &FragShaderSolid : &FragShaderNotSolid, nullptr);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            throw ShaderCompileError(fragmentShader);
        }

        /*Shader program attachment and linking*/
        glAttachShader(this->ShaderProgram, vertexShader);
        glAttachShader(this->ShaderProgram, fragmentShader);
        glLinkProgram(this->ShaderProgram);

        glGetProgramiv(this->ShaderProgram, GL_LINK_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            throw ShaderCompileError(this->ShaderProgram);
        }

        /*Deletion*/
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }

    SPProc Material::GetShaderProgram() const
    {
        return this->ShaderProgram;
    }

    bool Material::GetIsSolid() const
    {
        return IsSolid;
    }

    void Material::UpdateGLMatrix(glm::mat4 matrix, const std::string& name) const
    {
        glUseProgram(this->ShaderProgram);

        const GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str());

        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    const char* Material::VertexShaderSolid = "#version 330 core\n"

        "layout (location = 0) in vec3 Pos;\n"

        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"

        "void main()\n"
        "{\n"
        " gl_Position =  projection * view * model * vec4(Pos, 1.0);\n"
        "}\0";


    const char* Material::FragShaderSolid = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 SolidColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = SolidColor;\n"
        "}\n";

    const char* Material::VertexShaderNotSolid = "#version 330 core\n"
        "layout (location = 0) in vec3 Pos;\n"
        "layout (location = 1) in vec4 Color;\n"

        "out vec4 OutColor;\n"

        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"

        "void main()\n"
        "{\n"
        " gl_Position = projection * view *  model * vec4(Pos, 1.0);\n"
        " OutColor = Color;\n"
        "}\0";

    const char* Material::FragShaderNotSolid = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 OutColor;\n"
        "void main()\n"
        "{\n"
        " FragColor = OutColor;\n"
        "}\n";
} // namespace basilisk
