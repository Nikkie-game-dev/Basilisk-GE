#pragma once

#include <memory>

#include "Export.h"
#include "glm/glm.hpp"

namespace basilisk
{
    using SPProc = unsigned int;

    class BASILISK_API Material
    {
    public:
        static std::shared_ptr<Material> New(bool isSolid);
        void BuildShader();

        [[nodiscard]] SPProc GetShaderProgram() const;
        [[nodiscard]] bool GetIsSolid() const;
        void UpdateGLModel(glm::mat4 modelMatrix) const;

        explicit Material(bool isSolid);

    private:
        bool IsSolid;
        SPProc ShaderProgram = 0;
        static const char* VertexShaderSolid;
        static const char* FragShaderSolid;
        static const char* VertexShaderNotSolid;
        static const char* FragShaderNotSolid;
    };
} // namespace basilisk 
