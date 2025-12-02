#include "BlueSquare.h"

BlueSquare::BlueSquare(float speed, glm::vec2 limits) : 
	Square({300.0f, 300.0f}, {300.0f, 300.0f}, true, basilisk::Color(0.0f,0.0f,255.0f,0.5f))
{
    this->MovingRight = true;
    this->Speed = speed;
    MinX = GetScale2D().x / 2;
    MaxX = limits.x - GetScale2D().x / 2;
    Delta = 0.0f;
}

void BlueSquare::Update()
{
    auto pos = GetPosition2D();

    if (pos.x >= MaxX || pos.x <= MinX)
        this->MovingRight = !this->MovingRight;

    if (this->MovingRight)
        pos.x += Speed * Delta;
    else
        pos.x -= Speed * Delta;

    SetPosition(pos);
}
