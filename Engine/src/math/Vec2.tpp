#ifndef VEC2_TPP
#define VEC2_TPP

#include "Vec2.h"

namespace basilisk::math
{
    template <Number N>
    Vec2<N>::Vec2(N x, N y)
    {
        this->X = x;
        this->Y = y;
    }
}

#endif // VEC2_TPP
