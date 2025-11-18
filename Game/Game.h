#pragma once

#include "BaseGame.h"
#include "Character.h"

namespace game
{
    class Game : public BaseGame
    {
    public:
        Game(const char* windowName, float sizeX, float sizeY);
        ~Game() = default;
        void Init() override;
        void Update() override;
        void Draw() override;

    private:
        Character Eliwood;
        Character Eirika;
    };

} // namespace game
