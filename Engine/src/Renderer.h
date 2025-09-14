#pragma once

#include <string>

#ifdef _WIN32
#ifdef BASILISK_EXPORT
#define BASILISK_API __declspec(dllexport)
#define BASILISK_EXTERN
#else
#define BASILISK_API __declspec(dllimport)
#define BASILISK_EXTERN extern
#endif
#endif

namespace basilisk
{

    using BufferProc = unsigned int;
    using ShaderProc = unsigned int;
    using SPProc = unsigned int;

    class BASILISK_API Renderer
    {
    public:
        void InitGLFW();
        void SetGlVersion();
        void InitGL() const;
        void GenerateVBs(float vertices[], unsigned int indices[], int amountVertices, int amountIndices);
        void Draw(int verticesAmount) const;
        void StartDraw();
        void EndDraw() const;
        static Renderer& GetInstance();
        void BuildShaders();

        Renderer(const Renderer& other) = delete;            // copy constructor
        Renderer(Renderer&& other) = delete;                 // move constructor
        Renderer& operator=(const Renderer& other) = delete; // copy assignment
        Renderer& operator=(Renderer&& other) = delete;      // move assignment


    private:
        Renderer() = default;
        ~Renderer() = default;
        BufferProc Vbo;
        BufferProc Vao;
        BufferProc Ebo;
        SPProc ShaderProg;

        void PopulateVBO() const;
        void PopulateEBO() const;
        void UpdateVertexAttributes() const;
        void UnbindVertexArray() const;
        void BindVertexArray() const;
        void GenerateVAO();
        void GenerateVBO();
        void GenerateEBO();
    };

    
} // namespace basilisk
