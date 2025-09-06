#include "Basilisk/BaseGame.h"

int main()
{
    auto engine = basilisk::BaseGame("Test", 600, 600);
    engine.BuildShader();
    
    while (!engine.WindowShouldClose())
    {
        engine.StartDraw();
        engine.Draw();
        engine.EndDraw();
    }
}
