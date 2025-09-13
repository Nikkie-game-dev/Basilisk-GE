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

}// namespace basilisk
