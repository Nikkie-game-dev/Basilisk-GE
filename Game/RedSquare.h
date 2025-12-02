#pragma once

#include "Basilisk/InputAction.h"
#include "Basilisk/Square.h"

namespace game
{
    class RedSquare : public basilisk::Square
    {
    public:
        RedSquare(float speed);

        void Update() override;
        float Delta;
        basilisk::InputAction* ScaleUp = nullptr;
        basilisk::InputAction* ScaleDown = nullptr;
        basilisk::InputAction* RotateCW = nullptr;
        basilisk::InputAction* RotateCCW = nullptr;

    private:
        float Speed;
    };
} // namespace game
