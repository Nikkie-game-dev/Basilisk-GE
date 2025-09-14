#pragma once

#include "Colors.h"
#include "Entity2D.h"
#include "Export.h"

namespace basilisk
{

    class BASILISK_API Shape : public Entity2D
    {
    public:
        Shape(Color color, glm::vec2 size, glm::vec2 position = {0,0} , glm::vec2 rotation = {0,0});
        virtual ~Shape() = default;
        void Init() override;
        void Draw() override;

    private:
        Color Color;
    };
} // basilisk 
