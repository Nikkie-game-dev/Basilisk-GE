#pragma once

#include "Export.h"

namespace basilisk
{
    using SPProc = unsigned int;

    class BASILISK_API Material
    {
    public:
        void BuildShader();
        [[nodiscard]] SPProc GetShaderProgram() const;

    private:
        SPProc ShaderProgram = 0;
    };
} // namespace basilisk 
