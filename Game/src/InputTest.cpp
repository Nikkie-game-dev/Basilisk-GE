#include "InputTest.h"

namespace game
{

    InputTest::InputTest(const glm::vec2& size, const glm::vec2& position) :
        Square(position, size, true, basilisk::Color::Red)
    {
    }

    void InputTest::Update()
    {
        if (this->Action->IsDown())
        {
            this->SetPosition({500, 600});
        }
        else
        {
            this->SetPosition({100, 600});
        }
    }

} //namespace game
