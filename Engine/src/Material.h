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
        /// <summary>
        /// Constructor for material. It is not recommended to use this function, but use New().
        /// </summary>
        /// <param name="isSolid">If the color is supplied by the vertices or if it is supplied by the program (solid color).</param>
        explicit Material(bool isSolid);

        /// <summary>
        /// Constructs materials and returns a shared pointer with the material.
        /// </summary>
        /// <param name="isSolid">If the color is supplied by the vertices or if it is supplied by the program (solid color).</param>
        /// <returns>Shared pointer with new Material</returns>
        static std::shared_ptr<Material> New(bool isSolid);

        /// <summary>
        /// Builds and compiles shaders.
        /// </summary>
        void BuildShader();


        /// <summary>
        /// Getter for Shader Program.
        /// </summary>
        /// <returns>Shader Program index.</returns>
        [[nodiscard]] SPProc GetShaderProgram() const;

        /// <summary>
        /// Getter for IsSolid Flag
        /// </summary>
        /// <returns>If the material is supplied by the vertices or if it is supplied by the program</returns>
        [[nodiscard]] bool GetIsSolid() const;
        
        /// <summary>
        /// Sends a matrix to OpenGl.
        /// </summary>
        /// <param name="matrix">Matrix to send to OpenGl.</param>
        /// <param name="name">Name of Matrix in Shader source</param>
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
