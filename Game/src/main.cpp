#include "Game.h"

int main()
{
    auto engine = new Game("Test", 600, 600);
    engine->Run();
    delete engine;
}
