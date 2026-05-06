#include "RotatingCube.h"

namespace game
{
    void RotatingCube::Update()
    {
        this->SetRotation(this->GetRotation().z + 0.5f, basilisk::Axis::Z, false);
    }
}
