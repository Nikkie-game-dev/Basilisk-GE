#pragma once

#include <list>

#include "Export.h"
#include "InputAction.h"

namespace basilisk
{
    class Window;
    
    class BASILISK_API Input
    {
    public:
        explicit Input(Window* window);
        ~Input();

        InputAction& NewInput(Keys key);
        void StopUpdatingInput(InputAction& inputAction);

        void UpdateInputs();

    private:
        Window* Window = nullptr;
        std::list<InputAction*> InputActions;
    };
} // namespace basilisk 
