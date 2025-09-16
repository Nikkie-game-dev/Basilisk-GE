#include "OrangeSquare.h"

namespace game
{

    OrangeSquare::OrangeSquare(const glm::vec2& size, const glm::vec2& position, const float rotation) : 
        Square(position, size, true, basilisk::Color::Purple)
    {
    }

    OrangeSquare::OrangeSquare(const glm::vec2& size) : 
        Square({0.0f, 0.0f}, size, true, basilisk::Color::Yellow)
    {
    }
    
    void OrangeSquare::Update()
    {
        
    }
}
