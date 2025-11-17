#pragma once

#include <list>

#include "Export.h"
#include "InputAction.h"

namespace basilisk
{
    class Window;
    /// <summary>
    /// Input system that handles updating and constructing all input actions.
    /// </summary>
    class BASILISK_API Input
    {
    public:
        /// <summary>
        /// Constructs the input system. It is not needed to create it in a game, as BaseGame already comes with one.
        /// </summary>
        /// <param name="window">Window to provide context</param>
        explicit Input(Window* window);
        
        ~Input();

        /// <summary>
        /// Makes a New input action.
        /// </summary>
        /// <param name="key">Key to register</param>
        /// <returns>New Input Action</returns>
        InputAction& NewInput(Keys key);

        /// <summary>
        /// Stops and removes an input action.
        /// </summary>
        /// <param name="inputAction">Input action to remove</param>
        void StopUpdatingInput(InputAction& inputAction);

        /// <summary>
        /// Updates all registered input action's state.
        /// </summary>
        void UpdateInputs();

    private:
        Window* Window = nullptr;
        std::list<InputAction*> InputActions;
    };
} // namespace basilisk 
