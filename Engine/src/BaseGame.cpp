#include "BaseGame.h"

namespace basilisk
{

    BaseGame::BaseGame(const std::string& windowName, const math::Vec2<int> size)
    {
        if (!glfwInit())
        {
            throw CouldNotStartGlfw();
        }

        this->Window = basilisk::Window(windowName, size);
        this->Renderer = basilisk::Renderer();


        if (!gladLoadGL(glfwGetProcAddress))
        {
            throw CouldNotStartGlad();
        }

        Renderer.GenerateVBs();
    }



    void BaseGame::StartDraw() const
    {
        Renderer.StartDraw();
    }



    void BaseGame::Draw() const
    {
        Renderer.Draw();
    }



    void BaseGame::EndDraw() const
    {
        glfwSwapBuffers(this->Window.GetWindow());
        glfwPollEvents();
    }



    void BaseGame::Close() const
    {
        glfwTerminate();
    }



    void BaseGame::PopulateVbo()
    {
        // todo: recieve by param
        float vertices[] =
        {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    }



    void BaseGame::CompileShaders()
    {

        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char* fragShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n";


        const ShaderProc vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const ShaderProc fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        this->ShaderProg = glCreateProgram();

        GLint hasCompiled; //GL_TRUE OR GL_FALSE

        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            throw ShaderCompileError(vertexShader);
        }


        /*Compile frag shader*/
        glShaderSource(fragmentShader, 1, &fragShaderSource, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            throw ShaderCompileError(fragmentShader);
        }

        /*Shader program attachment and linking*/
        glAttachShader(this->ShaderProg, vertexShader);
        glAttachShader(this->ShaderProg, fragmentShader);
        glLinkProgram(this->ShaderProg);

        glGetProgramiv(this->ShaderProg, GL_LINK_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            throw ShaderCompileError(this->ShaderProg);
        }

        /*Deletion*/
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);


    }
}
