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
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

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
