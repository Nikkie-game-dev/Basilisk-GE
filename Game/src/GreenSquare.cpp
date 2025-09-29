#include "GreenSquare.h"

namespace game
{
    GreenSquare::GreenSquare(const glm::vec2& size, const glm::vec2& position, const float rotation) :
        Square(position, size, true, basilisk::Color::Green)
    {
    }

    GreenSquare::GreenSquare(const glm::vec2& size) : 
        Square({0.0f, 0.0f}, size, true, basilisk::Color::Green)
    {
    }

    void GreenSquare::Update()
    {
    }
} // namespace game
