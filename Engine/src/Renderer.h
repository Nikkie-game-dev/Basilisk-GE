#pragma once

#include "Export.h"
#include "glm/glm.hpp"
#include "Buffers.h"

namespace basilisk
{
    class Window;
    class Color;

    using ShaderProc = unsigned int;
    using SPProc = unsigned int;

    /// <summary>
    /// Singleton that is in charge to make the calls to OpenGl for drawing and rendering.
    /// </summary>
    class BASILISK_API Renderer
    {
    public:
        
#pragma region Loading
        /// <summary>
        /// Initializes GLFW.
        /// </summary>
        void InitGLFW();

        /// <summary>
        /// Sets upp which version of OpenGl we are using through hints.
        /// </summary>
        void SetGlVersion();

        /// <summary>
        /// Initializes GLEW.
        /// </summary>
        void InitGL() const;

        /// <summary>
        /// Loads an orthogonal projection matrix. Should be called once.
        /// </summary>
        void LoadProjectionMatrix();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="bufferID">Id of buffer to fill and bind</param>
        /// <param name="sizeArray">Size of array to fill buffer with</param>
        /// <param name="array">Array of data</param>
        static void BindAndFill(unsigned int bufferID, int sizeArray, float array[]);
        
        /// <copydoc href="BindAndFill">
        static void BindAndFill(unsigned int bufferID, int sizeArray, unsigned int array[]);

        /// <summary>
        /// Sets attribute pointer.
        /// </summary>
        /// <param name="index">Index of value to set</param>
        /// <param name="size">Amount of vertices per value</param>
        /// <param name="strideAmount">Size of stride</param>
        /// <param name="start">Start of value</param>
        static void SetAttribPointer(int index, int size, int strideAmount, int start);

#pragma endregion
        
#pragma region Drawing
        /// <summary>
        /// Generates vertex array object, vertex buffer object and elements buffer object.
        /// </summary>
        /// <param name="buffers">Buffers to pass to OpenGl</param>
        /// <param name="isSolid">Whether the object being drawn is a solid color or the vertex data includes per vertex color data</param>
        void GenerateVBs(Buffers& buffers, bool isTextured);
        
        /// <summary>
        /// Draws non-solid color objects.
        /// </summary>
        /// <param name="shaderProg">Process ID from the shader program</param>
        /// <param name="vao">Vertex Array Object</param>
        /// <param name="amountIndices">Amount of indices</param>
        void Draw(SPProc shaderProg, unsigned int& vao, int amountIndices) const;
        
        [[deprecated]] void Draw(SPProc shaderProg, unsigned int& vao, int amountIndices, Color color) const;

        /// <summary>
        /// Makes Pre-draw calls.
        /// </summary>
        void StartDraw();

        /// <summary>
        /// Makes post draw calls.
        /// </summary>
        void EndDraw() const;

        /// <summary>
        /// Updates the view matrix. This function only works with a unique camera.
        /// </summary>
        void UpdateViewMatrix();
        
#pragma endregion

#pragma region Getters
        /// <summary>
        /// Only access to the singleton unique instance. If no instance has been created, it creates an instance.
        /// </summary>
        /// <returns>Reference to instance</returns>
        static Renderer& GetInstance();

        /// <summary>
        /// Getter for the up vector of the camera.
        /// </summary>
        /// <returns>Camera's Up Vector</returns>
        [[nodiscard]] glm::vec3 GetCameraUp() const;

        /// <summary>
        /// Getter for the targeted position of the camera.
        /// </summary>
        /// <returns>Camera's targeted position</returns>
        [[nodiscard]] glm::vec3 GetCameraTarget() const;

        /// <summary>
        /// Getter for the position of the camera.
        /// </summary>
        /// <returns>Camera's Position</returns>
        [[nodiscard]] glm::vec3 GetCameraPos() const;

        /// <summary>
        /// Getter for the projection matrix.
        /// </summary>
        /// <returns>Projection Matrix</returns>
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const;

        /// <summary>
        /// Getter for the view matrix.
        /// </summary>
        /// <returns>View Matrix</returns>
        [[nodiscard]] glm::mat4 GetViewMatrix() const;
#pragma endregion

#pragma region Setters
        /// <summary>
        /// Sets the reference for the window that's being rendered
        /// </summary>
        /// <param name="window">Window to work on</param>
        void SetWindowRef(Window& window);
        
#pragma endregion

        
        Renderer(const Renderer& other) = delete;            // copy constructor
        Renderer(Renderer&& other) = delete;                 // move constructor
        Renderer& operator=(const Renderer& other) = delete; // copy assignment
        Renderer& operator=(Renderer&& other) = delete;      // move assignment

    private:
        Renderer();
        ~Renderer() = default;
        
        glm::vec3 CameraPos;
        glm::vec3 CameraUp;
        glm::vec3 CameraTarget;
        
        glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 ViewMatrix = glm::mat4(1.0f);

        Window* Window;
    };

    
} // namespace basilisk
