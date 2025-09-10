#include "Game.h"

int main()
{
    auto game = new Game("Test", 600, 600);
    game->Run();
    delete game;
}
