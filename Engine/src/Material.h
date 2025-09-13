#pragma once

#include "Export.h"

namespace basilisk
{
    using SPProc = unsigned int;

    class BASILISK_API Material
    {
    public:
        void BuildShader(bool isSolid);
        
        [[nodiscard]] SPProc GetShaderProgram() const;

    private:
        SPProc ShaderProgram = 0;
    };

    static const auto* VertexShaderSolid =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    
    static const auto* FragShaderSolid =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 SolidColor"
        "void main()\n"
        "{\n"
        "FragColor = SolidColor;\n"
        "}\n";
} // namespace basilisk 
