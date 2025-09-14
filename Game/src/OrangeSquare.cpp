#include "OrangeSquare.h"

namespace game
{

    OrangeSquare::OrangeSquare(const glm::vec2& size, const glm::vec2& position, const glm::vec2& rotation) :
        Shape(basilisk::Color::Yellow, size, position, rotation)
    {
    }

    OrangeSquare::OrangeSquare(const glm::vec2& size) :
       Shape(basilisk::Color::Yellow, size)
    {
    }
    
    void OrangeSquare::Update()
    {
        
    }
}
