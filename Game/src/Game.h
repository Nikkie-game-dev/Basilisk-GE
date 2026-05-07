#pragma once
#include "BaseGame.h"
#include "RotatingCube.h"

namespace game
{
    class Game final : public basilisk::BaseGame
    {
    public:
        Game(const char* windowName, float sizeX, float sizeY);
        ~Game() = default;

    protected:
        void Init() override;
        void Update() override;
        void Draw() override;
        RotatingCube RotCube;

        std::shared_ptr<basilisk::Camera> FirstPerson = std::make_shared<basilisk::Camera>(
            glm::vec3({20, 20, 20}), RotCube.GetPositionPtr());
        std::shared_ptr<basilisk::Camera> ThirdPerson = std::make_shared<basilisk::Camera>(
            glm::vec3({20, 20, 20}), RotCube.GetPositionPtr());
    };

} // namespace game
