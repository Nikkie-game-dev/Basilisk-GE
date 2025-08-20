#define GLFW_INCLUDE_NONE

#include <glad/gl.h> // needed because glfw3 only includes opengl 1.2
#include <GLFW/glfw3.h>
#include <iostream>



int main()
{
    GLFWwindow* window;
    int success;


    /*Buffers*/
    GLuint vao; // Vertex Array Object
    GLuint vbo; // Vertex Buffer Object

    /*Shaders*/
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";


    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    
    /*vertices of triangle */
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    /*Vertex Shader Object*/
    unsigned int vertexShader;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*Init glad*/
    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    /*VAO gen*/
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /*Gen, bind, and populate vbo*/
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*Create vso and compile*/
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        abort();
    }


    
    /*Deletion*/
    glDeleteShader(vertexShader);

    /*Vertex Attribute*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
