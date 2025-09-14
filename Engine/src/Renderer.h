#pragma once

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
    class Color;

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
        void Draw(SPProc ShaderProg) const;
        void Draw(SPProc ShaderProg, Color color) const;
        void StartDraw();
        void EndDraw() const;
        static Renderer& GetInstance();
        
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
    };

    
} // namespace basilisk
