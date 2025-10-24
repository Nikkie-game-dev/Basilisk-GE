#include "Input.h"

namespace basilisk
{

    Input::Input(basilisk::Window* window) :
        Window(window)
    {
    }

    Input::~Input()
    {
        for (const auto inputAction : this->InputActions)
        {
            delete inputAction;
        }
    }

    InputAction& Input::NewInput(Keys key)
    {
        auto newIA = new InputAction(this->Window, key);
        this->InputActions.push_back(newIA);

        return *newIA;
    }

    void Input::StopUpdatingInput(InputAction& inputAction)
    {
        this->InputActions.remove(&inputAction);
    }

    void Input::UpdateInputs() 
    {
        for (auto inputAction : this->InputActions)
        {
            if (inputAction != nullptr)
            {
                inputAction->Update();
            }
        }
    }

} //namespace basilisk
