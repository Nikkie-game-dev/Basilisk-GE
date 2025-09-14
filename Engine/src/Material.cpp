#include "Material.h"

#include <GL/glew.h>

#include "RenderException.h"

namespace basilisk
{
    using ShaderProc = unsigned int;

    void Material::BuildShader(bool isSolid)
    {
        const ShaderProc vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const ShaderProc fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        
        this->ShaderProgram = glCreateProgram();

        GLint hasCompiled;

        if (isSolid)
        {
            glShaderSource(vertexShader, 1, &VertexShaderSolid, nullptr);
        }
        else
        {
            //TODO
        }
        
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            throw ShaderCompileError(vertexShader);
        }


        /*Compile frag shader*/
        if (isSolid)
        {
            glShaderSource(fragmentShader, 1, &FragShaderSolid, nullptr);
        }
        {
            //TODO
        }
        
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

    const char* Material::VertexShaderSolid =
        "#version 330 core\n"
        "layout (location = 0) in vec3 Pos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(Pos.x, Pos.y, Pos.z, 1.0);\n"
        "}\0";

    const char* Material::FragShaderSolid =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 SolidColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = SolidColor;\n"
        "}\n";

    const char* Material::VertexShaderNotSolid =
        "#version 330 core\n"
        "layout (location = 0) in vec3 Pos;\n"
        "layout (location = 1) in vec4 Color;\n"
        "out vec4 OutColor;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(Pos.x, Pos.y, Pos.z, 1.0);\n"
        " OutColor = Color;\n"
        "}\0";

    const char* Material::FragShaderNotSolid =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 OutColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = OutColor;\n"
        "}\n";
} // namespace basilisk
