#include "Colors.h"
#include <cfloat>

namespace basilisk
{
    // Color palette from https://coolors.co/palette/f00314-ff8019-fae603-28e10a-3bb5ff-0500c7-5c03fa-de00ed

    void Color::Normalize(const Color& color)
    {
        this->R = static_cast<float>(color.R) / static_cast<float>(MaxValue);
        this->G = static_cast<float>(color.G) / static_cast<float>(MaxValue);
        this->B = static_cast<float>(color.B) / static_cast<float>(MaxValue);
        this->A = color.A;
    }

    Color::Color(const unsigned char& r, const unsigned char& g, const unsigned char& b, const float a)
    {
        this->R = r < 1.0f + FLT_EPSILON ? static_cast<unsigned char>(r * static_cast<float>(MaxValue)) : r;
        this->G = g < 1.0f + FLT_EPSILON ? static_cast<unsigned char>(g * static_cast<float>(MaxValue)) : g;
        this->B = b < 1.0f + FLT_EPSILON ? static_cast<unsigned char>(b * static_cast<float>(MaxValue)) : b;

        if (a >= MaxValueAlpha)
        {
            this->A = 1.0;
        }
        else if (a <= MinValueAlpha)
        {
            this->A = 0.0;
        }
        else
        {
            this->A = a;
        }
    }

    Color::Color(const unsigned char& r, const unsigned char& g, const unsigned char& b) : R(r), G(g), B(b), A(1.0)
    {
    }

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
} // namespace basilisk
