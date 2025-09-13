#pragma once
#include "Basilisk/Entity2D.h"

namespace game
{
    class Square final : public basilisk::Entity2D
    {
    public:
        void Init() override;
        void Update() override;
        
    };
} // game 
