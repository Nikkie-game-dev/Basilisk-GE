#pragma once

#include "Export.h"

#include <string>

namespace basilisk
{
    class Window;
    class Renderer;

    /// <summary>
    /// Abstract class to be inherited by Game
    /// </summary>
    class BASILISK_API BaseGame
    {
    public:
        /// <summary>
        /// Constructor for BaseGame
        /// </summary>
        /// <param name="windowName">Name to set the window</param>
        /// <param name="sizeX">Width in pixels for the size of the window</param>
        /// <param name="sizeY">Height in pixels for the size of the window</param>
        BaseGame(const std::string& windowName, int sizeX, int sizeY);

        virtual ~BaseGame();

        /// <summary>
        /// Copy constructor
        /// </summary>
        /// <param name="other">Other BaseGame to copy from</param>
        BaseGame(const BaseGame& other);

        /// <summary>
        /// Move Constructor
        /// </summary>
        /// <param name="other">Other BaseGame to move from</param>
        BaseGame(BaseGame&& other) noexcept;

        /// <summary>
        /// Copy Assignment
        /// </summary>
        /// <param name="other">Other BaseGame to copy from</param>
        /// <returns>Copied BaseGame</returns>
        BaseGame& operator=(const BaseGame& other);

        /// <summary>
        /// Move assignment
        /// </summary>
        /// <param name="other">Other BaseGame to from</param>
        /// <returns>Moved BaseGame</returns>
        BaseGame& operator=(BaseGame&& other) noexcept; // move assignment

        /// <summary>
        /// Main loop
        /// </summary>
        void Run();

    protected:
        /// <summary>
        /// Abstract function to be implemented by Game. Called last in engine loop, between EndDraw and StartDraw
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// Abstract function to be implemented by Game. Called before the engine loop
        /// </summary>
        virtual void Init() = 0;

        /// <summary>
        /// Abstract function to be implemented by Game. Called before Draw() in engine loop
        /// </summary>
        virtual void Update() = 0;


        /// <summary>
        /// Checks that whether the signal to close window has been received
        /// </summary>
        /// <returns>State of signal</returns>
        [[nodiscard]] bool WindowShouldClose() const;

        /// <summary>
        /// Called after the engine loop to eliminate created objects
        /// </summary>
        void Close() const;

        float GetDelta();
        
        Renderer& Renderer;
        
    private:
        std::string WindowName;
        int X;
        int Y;
        float Delta = 0;
        Window* Window;
    };

} // namespace basilisk
