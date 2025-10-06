#include "GreenSquare.h"

namespace game
{
    GreenSquare::GreenSquare(const glm::vec2& size, const glm::vec2& position) :
        Square(position, size, true, basilisk::Color::Green)
    {
    }

    void GreenSquare::Update()
    {
    }
} // namespace game
