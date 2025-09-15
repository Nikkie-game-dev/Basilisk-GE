#include "Shape.h"

#include "Renderer.h"

namespace basilisk
{
    
    Shape::Shape(const basilisk::Color color, const glm::vec2 size, const glm::vec2 position, const glm::vec2 rotation) :
        Entity2D(false), Color(color)
    {
        this->Scaling = size;
        this->Position = position;
        this->Rotation = rotation;
    }

    void Shape::Init()
    {
        float vertices[] = {
            //    POSITION            |        COLOR
            0.5f,  0.5f,  0.0f,       1.0f, 0.0f, 0.0f, 1.0f,  // top right
            0.5f,  -0.5f, 0.0f,       0.0f, 1.0f, 0.0f, 1.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f, 1.0f,  // bottom left
            -0.5f, 0.5f,  0.0f,       1.0f, 1.0f, 1.0f, 0.0f   // top left
        };

        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };
        
        FillIndices(indices, sizeof(indices));
        FillVertices(vertices, sizeof(vertices));

        UpdateBuffers();

        Mat.BuildShader();
    }
    
    void Shape::Draw()
    {
        Renderer::GetInstance().Draw(Mat.GetShaderProgram());
    }
    
}// basilisk
