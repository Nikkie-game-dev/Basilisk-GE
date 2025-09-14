#include "Colors.h"

namespace basilisk
{
    // Color palette from https://coolors.co/palette/f00314-ff8019-fae603-28e10a-3bb5ff-0500c7-5c03fa-de00ed

    const Color Color::Red = Color(255, 3, 20);
    const Color Color::Orange = Color(255, 128, 25);
    const Color Color::Yellow = Color(250, 230, 3);
    const Color Color::Green = Color(40, 225, 10);
    const Color Color::Cyan = Color(59, 181, 255);
    const Color Color::DeepBlue = Color(5, 0, 199);
    const Color Color::Blue = Color(92, 3, 250);
    const Color Color::Purple = Color(222, 0, 237);

    const unsigned char Color::MaxValue = 255;
    const float Color::MaxValueAlpha = 1.0;
    const float Color::MinValueAlpha = 0.0;
}