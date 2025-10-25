#include "InputAction.h"
#include <unordered_map>
#include "Window.h"

namespace basilisk
{
    static const std::unordered_map<Keys, int> keyMap = {
        {Keys::ESC, GLFW_KEY_ESCAPE},
        {Keys::ENTER, GLFW_KEY_ENTER},
        {Keys::BACKSPACE, GLFW_KEY_BACKSPACE},
        {Keys::A, GLFW_KEY_A},
        {Keys::B, GLFW_KEY_B},
        {Keys::C, GLFW_KEY_C},
        {Keys::D, GLFW_KEY_D},
        {Keys::E, GLFW_KEY_E},
        {Keys::F, GLFW_KEY_F},
        {Keys::G, GLFW_KEY_G},
        {Keys::H, GLFW_KEY_H},
        {Keys::I, GLFW_KEY_I},
        {Keys::J, GLFW_KEY_J},
        {Keys::K, GLFW_KEY_K},
        {Keys::L, GLFW_KEY_L},
        {Keys::M, GLFW_KEY_M},
        {Keys::N, GLFW_KEY_N},
        {Keys::O, GLFW_KEY_O},
        {Keys::P, GLFW_KEY_P},
        {Keys::Q, GLFW_KEY_Q},
        {Keys::R, GLFW_KEY_R},
        {Keys::S, GLFW_KEY_S},
        {Keys::T, GLFW_KEY_T},
        {Keys::U, GLFW_KEY_U},
        {Keys::V, GLFW_KEY_V},
        {Keys::W, GLFW_KEY_W},
        {Keys::X, GLFW_KEY_X},
        {Keys::Y, GLFW_KEY_Y},
        {Keys::Z, GLFW_KEY_Z},         
        {Keys::NUM_0, GLFW_KEY_0},
        {Keys::NUM_1, GLFW_KEY_1},
        {Keys::NUM_2, GLFW_KEY_2},
        {Keys::NUM_3, GLFW_KEY_3},
        {Keys::NUM_4, GLFW_KEY_4},
        {Keys::NUM_5, GLFW_KEY_5},
        {Keys::NUM_6, GLFW_KEY_6},
        {Keys::NUM_7, GLFW_KEY_7},
        {Keys::NUM_8, GLFW_KEY_8},
        {Keys::NUM_9, GLFW_KEY_9},
        {Keys::LEFT_ALT, GLFW_KEY_LEFT_ALT},
        {Keys::RIGHT_ALT, GLFW_KEY_RIGHT_ALT},
        {Keys::SHIFT, GLFW_KEY_LEFT_SHIFT},
        {Keys::CTRL, GLFW_KEY_LEFT_CONTROL}
    };

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
        return key == Keys::UNSET ? 0 : keyMap.at(key);
    }

} //namespace basilisk
