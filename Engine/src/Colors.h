#pragma once

namespace basilisk
{
    constexpr unsigned char MaxValue = 255;
    constexpr float MaxValueAlpha = 1.0;
    constexpr float MinValueAlpha = 0.0;

    class Color
    {
    public:
        Color(const unsigned char r, const unsigned char g, const unsigned char b, const float a)
        {
            this->R = r;
            this->G = g;
            this->B = b;

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

        Color(const unsigned char r, const unsigned char g, const unsigned char b) :
            R(r), G(g), B(b), A(1.0)
        {
        }

        unsigned char R;
        unsigned char G;
        unsigned char B;
        float A;
    };

    // Color palette from https://coolors.co/palette/f00314-ff8019-fae603-28e10a-3bb5ff-0500c7-5c03fa-de00ed

    const static auto Red = Color(255, 3, 20);
    const static auto Orange = Color(255, 128, 25);
    const static auto Yellow = Color(250, 230, 3);
    const static auto Green = Color(40, 225, 10);
    const static auto Cyan = Color(59, 181, 255);
    const static auto DeepBlue = Color(5, 0, 199);
    const static auto Blue = Color(92, 3, 250);
    const static auto Purple = Color(222, 0, 237);
}// namespace basilisk
