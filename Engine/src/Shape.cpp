#include "Shape.h"

#include "Renderer.h"

namespace basilisk
{
    void Shape::Init()
    {
        const auto mat = this->GetMaterial();
        this->UpdateBuffers();

        mat->BuildShader();

        if (!mat->IsProjectionSent)
        {
            Renderer::GetInstance().LoadProjectionMatrix();
            mat->UpdateGLMatrix(Renderer::GetInstance().GetProjectionMatrix(), "projection");
            mat->IsProjectionSent = true;
        }
    }
    
    Shape::Shape(const basilisk::Color color, const bool isSolid) :
        IsSolid(isSolid)
    {
        this->Color = color;
    }
}
