#pragma once
#include "Export.h"

namespace basilisk
{
    /// <summary>
    /// Handles color values
    /// </summary>
    class BASILISK_API Color
    {

    public:
        class Normalize
        {
        public:
            /// <summary>
            /// Normalize a color
            /// </summary>
            /// <param name="color">Color to normalize</param>
            explicit Normalize(Color color);
            
            float R;
            float G;
            float B;
            float A;
        };

        /// <summary>
        /// Converts a normalized color into a color.
        /// </summary>
        /// <param name="normalizedColor">Color that is within 1.0f and 0.0f</param>
        Color(const Normalize& normalizedColor);
        
        /// <summary>
        /// Constructor for Color, with a transparency value. All values are from 0 to 255, except the transparency value that has a maximum
        /// of 1.0f, and a minimum of 0.0f.
        /// </summary>
        /// <param name="r">Red value</param>
        /// <param name="g">Green value</param>
        /// <param name="b">Blue vaue</param>
        /// <param name="a">Transparency value</param>
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

        /// <summary>
        /// Constructor for Color, without a transparency value. All values are from 0 to 255.
        /// </summary>
        /// <param name="r">Red value</param>
        /// <param name="g">Green value</param>
        /// <param name="b">Blue value</param>
        Color(const unsigned char r, const unsigned char g, const unsigned char b) :
            R(r), G(g), B(b), A(1.0)
        {
        }


        unsigned char R;
        unsigned char G;
        unsigned char B;
        float A;

        static const Color Red;
        static const Color Orange;
        static const Color Yellow;
        static const Color Green;
        static const Color Cyan;
        static const Color DeepBlue;
        static const Color Blue;
        static const Color Purple;

        static const unsigned char MaxValue;
        static const float MaxValueAlpha;
        static const float MinValueAlpha;

    };
} // namespace basilisk
