#pragma once

#include <memory>
#include <string>

#include "Export.h"
#include "glm/glm.hpp"

namespace basilisk
{
    using SPProc = unsigned int;

    class BASILISK_API Material
    {
    public:
        explicit Material(bool isSolid);
        static std::shared_ptr<Material> New(bool isSolid);
        void BuildShader();

        [[nodiscard]] SPProc GetShaderProgram() const;
        [[nodiscard]] bool GetIsSolid() const;
        void UpdateGLMatrix(glm::mat4 matrix, const std::string& name) const;

        bool IsProjectionSent = false;
        bool IsViewSent = false;
        
    private:
        bool IsSolid;
        SPProc ShaderProgram = 0;
        static const char* VertexShaderSolid;
        static const char* FragShaderSolid;
        static const char* VertexShaderNotSolid;
        static const char* FragShaderNotSolid;
    };
} // namespace basilisk 
