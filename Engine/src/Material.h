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
        static const char* VertexShaderSolid;
        static const char* FragShaderSolid;
    };
} // namespace basilisk 
