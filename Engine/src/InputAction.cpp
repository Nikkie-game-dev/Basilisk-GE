#include "InputAction.h"

#include "Window.h"

namespace basilisk
{
    InputAction::InputAction()
    {
        this->Window = nullptr;
        this->Key = ConvertKeys(Keys::UNSET);
    }

    InputAction::InputAction(basilisk::Window* window, const Keys& key) :
        Window(window),
        Key(ConvertKeys(key))
    {
    }

    bool InputAction::IsUp() const
    {
        return !this->IsCurrentlyDown;
    }

    bool InputAction::IsDown() const
    {
        return this->IsCurrentlyDown;
    }

    bool InputAction::IsPressedAndReleased() const
    {
        return !this->IsCurrentlyDown && this->WasDown;
    }

    void InputAction::Update()
    {
        if (!this->Window)
            return;

        const auto state = glfwGetKey(this->Window->GetWindow(), this->Key);

        if (state == GLFW_PRESS)
        {
            this->IsCurrentlyDown = true;
        }
        else if (this->IsCurrentlyDown)
        {
            this->IsCurrentlyDown = false;
            this->WasDown = true;
        }
        else if (this->WasDown)
        {
            this->WasDown = false;
        }

    }
    int InputAction::ConvertKeys(Keys key)
    {
        using enum Keys;

        switch (key)
        {
        case UNSET:
            return 0;
        case ESC:
            return GLFW_KEY_ESCAPE;
        case ENTER:
            return GLFW_KEY_ENTER;
        case BACKSPACE:
            return GLFW_KEY_BACKSPACE;
        case A:
        case B:
        case C:
        case D:
        case E:
        case F:
        case G:
        case H:
        case I:
        case J:
        case K:
        case L:
        case M:
        case N:
        case O:
        case P:
        case Q:
        case R:
        case S:
        case T:
        case U:
        case V:
        case W:
        case X:
        case Y:
        case Z:
            return GLFW_KEY_A + static_cast<int>(key) - static_cast<int>(A);
        case NUM_0:
        case NUM_1:
        case NUM_2:
        case NUM_3:
        case NUM_4:
        case NUM_5:
        case NUM_6:
        case NUM_7:
        case NUM_8:
        case NUM_9:
            return GLFW_KEY_0 + static_cast<int>(key) - static_cast<int>(NUM_0);
        case LEFT_ALT:
            return GLFW_KEY_LEFT_ALT;
        case RIGHT_ALT:
            return GLFW_KEY_RIGHT_ALT;
        case SHIFT:
            return GLFW_KEY_RIGHT_SHIFT;
        case CTRL:
            return GLFW_KEY_LEFT_CONTROL;
        default:
            return 0;
        }
    }

} //namespace basilisk
