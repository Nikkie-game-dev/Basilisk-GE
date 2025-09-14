#include "Renderer.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "RenderException.h"

namespace basilisk
{
    void Renderer::InitGLFW()
    {
        if (!glfwInit())
        {
            throw CouldNotStartGlfw();
        }
    }
    void Renderer::SetGlVersion()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void Renderer::InitGL() const
    {
        if (glewInit() != GLEW_OK)
        {
            throw CouldNotStartGlew();
        }
    }

    void Renderer::StartDraw()
    {
        BuildShaders();
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::EndDraw() const
    {
        glfwSwapBuffers(glfwGetCurrentContext());
        glfwPollEvents();
    }

    Renderer& Renderer::GetInstance()
    {
        static Renderer instance;
        return instance;
    }

    void Renderer::GenerateVBs(float vertices[], unsigned int indices[], const int amountVertices, const int amountIndices)
    {
        glGenVertexArrays(1, &this->Vao);
        glGenBuffers(1, &this->Vbo);
        glGenBuffers(1, &this->Ebo);

        glBindVertexArray(this->Vao);

        glBindBuffer(GL_ARRAY_BUFFER, this->Vbo);
        glBufferData(GL_ARRAY_BUFFER, amountVertices * sizeof(float), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->Ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, amountIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Renderer::Draw(int verticesAmount) const
    {
        glUseProgram(this->ShaderProg);
        glBindVertexArray(this->Vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::BuildShaders()
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

        GLint hasCompiled;

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
} // namespace basilisk
