#pragma once

#include "Export.h"

namespace basilisk
{
    class Window;
    
    enum class Keys
    {
        UNSET,
        ESC,
        ENTER,
        BACKSPACE,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        NUM_0,
        NUM_1,
        NUM_2,
        NUM_3,
        NUM_4,
        NUM_5,
        NUM_6,
        NUM_7,
        NUM_8,
        NUM_9,
        LEFT_ALT,
        RIGHT_ALT,
        SHIFT,
        CTRL,
    };    
    
    class BASILISK_API InputAction
    {
    public:
        InputAction();
        InputAction(Window* window, const Keys& key);

        [[nodiscard]] bool IsUp() const;
        [[nodiscard]] bool IsDown() const;
        [[nodiscard]] bool IsPressedAndReleased() const;

        void Update();
        
    private:
        static int ConvertKeys(Keys key);
        bool IsCurrentlyDown = false;
        bool WasDown = false;
        Window* Window;
        int Key;
    };
} // namespace basilisk 
