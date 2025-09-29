#pragma once

#include "Entity.h"
#include "Export.h"
#include "glm/glm.hpp"
#include "Buffers.h"

namespace basilisk
{
    class Window;
    class Color;

    using ShaderProc = unsigned int;
    using SPProc = unsigned int;

    class BASILISK_API Renderer
    {
    public:
        
#pragma region Loading
        void InitGLFW();
        void SetGlVersion();
        void InitGL(glm::ivec2 windowSize) const;
        void LoadProjectionMatrix();
        
#pragma endregion
        
#pragma region Drawing
        void GenerateVBs(Buffers& buffers, const bool isSolid);

        void Draw(SPProc shaderProg, unsigned int& Vao, const int amountIndices) const;
        void Draw(const SPProc shaderProg, unsigned int& Vao, const int amountIndices, const Color color) const;
        void StartDraw();
        void EndDraw() const;
        void UpdateViewMatrix();
#pragma endregion

#pragma region Getters
        static Renderer& GetInstance();
        [[nodiscard]] glm::vec3 GetCameraUp() const;
        [[nodiscard]] glm::vec3 GetCameraTarget() const;
        [[nodiscard]] glm::vec3 GetCameraPos() const;
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const;
        [[nodiscard]] glm::mat4 GetViewMatrix() const;
#pragma endregion

#pragma region Setters
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
