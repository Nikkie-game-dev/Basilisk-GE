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
    
    /// <summary>
    /// The input itself. It provides access to the keys.
    /// </summary>
    class BASILISK_API InputAction
    {
    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        InputAction();
        
        /// <summary>
        /// Constructor for the input action. It associates a window and a key to an action. 
        /// It should not be used by itself, as Input provides a constructor for this class.
        /// </summary>
        /// <param name="window">Window to associate context</param>
        /// <param name="key">Key to associate</param>
        InputAction(Window* window, const Keys& key);

        /// <summary>
        /// Checks if the key is currently not pressed.
        /// </summary>
        /// <returns>True if not pressed</returns>
        [[nodiscard]] bool IsUp() const;

        /// <summary>
        /// Checks if the key is currently pressed.
        /// </summary>
        /// <returns>True if pressed</returns>
        [[nodiscard]] bool IsDown() const;

        /// <summary>
        /// Checks if the key was not pressed in last frame but now is currently pressed.
        /// </summary>
        /// <returns>True if last frame was released and this frame is pressed</returns>
        [[nodiscard]] bool IsPressedAndReleased() const;

        /// <summary>
        /// Retrieves the key state.
        /// </summary>
        void Update();
        
    private:
        static int ConvertKeys(Keys key);
        bool IsCurrentlyDown = false;
        bool WasDown = false;
        Window* Window;
        int Key;
    };
} // namespace basilisk 
