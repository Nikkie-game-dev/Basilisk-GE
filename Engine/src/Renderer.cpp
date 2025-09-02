#include "Renderer.h"

#include <GLFW/glfw3.h>


using namespace basilisk;

Renderer::Renderer()
{

}

void Renderer::InitGLFW()
{
    if (!glfwInit())
        throw CouldNotStartGlfw();
}

void Renderer::InitGL() const
{
    if (!glewInit())
        throw CouldNotStartGlew();
}

void Renderer::StartDraw() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::EndDraw() const
{
    glfwSwapBuffers(glfwGetCurrentContext());
    glfwPollEvents();
}

void Renderer::GenerateVBs()
{
    GenerateVAO();
    GenerateVBO();
    PopulateVBO();
    UpdateVertexAttributes();
}

void Renderer::GenerateVAO()
{
    glGenVertexArrays(1, &this->Vao);
    glBindVertexArray(this->Vao); 
}

void Renderer::GenerateVBO()
{
    glGenBuffers(1, &this->Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->Vbo);
}

void Renderer::PopulateVBO() const
{
    // todo: receive by param
    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Renderer::UpdateVertexAttributes() const
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
}

void Renderer::UnbindVertexArray() const
{
    glBindVertexArray(0);
}

void Renderer::BindVertexArray(BufferProc vao) const
{
    glBindVertexArray(vao);
}

void Renderer::Draw() const
{
    /*BindVertexArray(this->Vao);*/
    glDrawArrays(GL_TRIANGLES, 0, 3);
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

    /*Build*/
    glUseProgram(this->ShaderProg);
}
