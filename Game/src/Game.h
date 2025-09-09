#pragma once
#include "Basilisk/BaseGame.h"
#include "Basilisk/Renderer.h"

using namespace basilisk;

class Game : public BaseGame
{
public:
    Game(const std::string& windowName, int sizeX, int sizeY);

private:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Draw() override;
    basilisk::Renderer& Renderer;
};
