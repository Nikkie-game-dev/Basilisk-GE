#pragma once
#include "Basilisk/CollisionManager.h"
#include "Basilisk/BaseGame.h"
#include "Obstacle.h"
#include "Samus.h"
#include "TransparentObs.h"


namespace game
{
    class Game : public basilisk::BaseGame
    {
    public:
        Game(const char* windowName, float sizeX, float sizeY);
        ~Game() = default;
        void Init() override;
        void Update() override;
        void Draw() override;

    private:
        Samus Player;
        Obstacle Obstacle;
        TransparentObs Obstacle2;
        basilisk::CollisionManager CM;
    };

} // namespace game
