#pragma once

#include <memory>
#include <string>

#include "Export.h"
#include "glm/glm.hpp"

namespace basilisk
{
    using SPProc = unsigned int;

    /// <summary>
    /// This class is in charged of shaders building and compilation.
    /// </summary>
    class BASILISK_API Material
    {
    public:
        /// <summary>
        /// Constructor for material. It is not recommended to use this function, but use New().
        /// </summary>
        /// <param name="isTextured">If the color is supplied by the vertices or if it is supplied by the program (solid color).</param>
        explicit Material(bool isTextured);

        /// <summary>
        /// Constructs materials and returns a shared pointer with the material.
        /// </summary>
        /// <param name="isTextured">If the color is supplied by the vertices or if it is supplied by the program (solid color).</param>
        /// <returns>Shared pointer with new Material</returns>
        static std::shared_ptr<Material> New(bool isTextured);

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
        /// Getter for IsTextured Flag
        /// </summary>
        /// <returns>If the material is set with a texture</returns>
        [[nodiscard]] bool GetIsTextured() const;
        
        /// <summary>
        /// Sends a matrix to OpenGl.
        /// </summary>
        /// <param name="matrix">Matrix to send to OpenGl.</param>
        /// <param name="name">Name of Matrix in Shader source</param>
        void UpdateGLMatrix(glm::mat4 matrix, const std::string& name) const;

        bool IsProjectionSent = false;
        bool IsViewSent = false;
        
    private:
        bool IsTextured;
        SPProc ShaderProgram = 0;
        static const char* VertexShader;
        static const char* FragShader;
        static const char* FragShaderTextureless;
    };
} // namespace basilisk 
