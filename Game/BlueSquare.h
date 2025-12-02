#pragma once
#include "Basilisk/Square.h"
class BlueSquare : public basilisk::Square
{

public:
    BlueSquare(float speed, glm::vec2 limits);
    void Update() override;

    float Delta;

private:
    bool MovingRight;
    float MaxX;
    float MinX;
    float Speed;
};
