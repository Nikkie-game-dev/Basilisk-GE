#pragma once

#include "Export.h"

namespace basilisk
{
    using SPProc = unsigned int;

    class BASILISK_API Material
    {
    public:
        Material(bool isSolid);
        void BuildShader();
        
        [[nodiscard]] SPProc GetShaderProgram() const;
        bool GetIsSolid() const;
        
    private:
        bool IsSolid;
        SPProc ShaderProgram = 0;
        static const char* VertexShaderSolid;
        static const char* FragShaderSolid;
        static const char* VertexShaderNotSolid;
        static const char* FragShaderNotSolid;
    };
} // namespace basilisk 
