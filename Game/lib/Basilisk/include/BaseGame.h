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

//class Window;

#include <string>

namespace basilisk
{
    class BASILISK_API BaseGame
    {
    public:
        BaseGame(const std::string& windowName, int sizeX, int sizeY);
        ~BaseGame();
        void Draw() const;
        void Close() const;

    /*private:
        Window *window;*/
    };
    
} // basilisk 
