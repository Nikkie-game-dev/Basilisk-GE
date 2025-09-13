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
} // namespace basilisk
