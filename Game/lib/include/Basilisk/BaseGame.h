#pragma once

#pragma region Export
#ifdef _WIN32
#ifdef BASILISK_EXPORT
#define BASILISK_API __declspec(dllexport)
#define BASILISK_EXTERN
#else
#define BASILISK_API __declspec(dllimport)
#define BASILISK_EXTERN extern
#endif
#endif
#pragma endregion


#include <string>

namespace basilisk
{
    class Window;
    class Renderer;

    class BASILISK_API BaseGame
    {
    public:
        BaseGame(const std::string& windowName, int sizeX, int sizeY);
        ~BaseGame();
        BaseGame(const BaseGame& other); // copy constructor
        BaseGame(BaseGame&& other) noexcept; // move constructor
        BaseGame& operator=(const BaseGame& other); // copy assignment
        BaseGame& operator=(BaseGame&& other) noexcept; // move assignment

        void Run();

    protected:
        virtual void Draw();
        virtual void Init();
        virtual void Update() = 0;
        bool WindowShouldClose() const;
        void Close() const;
        Renderer& Renderer;

    private:
        std::string WindowName;
        int X;
        int Y;
        Window* Window;
    };

} // namespace basilisk
