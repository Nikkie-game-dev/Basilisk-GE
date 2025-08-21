#pragma once
#include <type_traits>

#include "../Export.h"

namespace basilisk::math
{
    template<typename T> concept Number = std::is_arithmetic_v<T>;

    template<Number N>
    BASILISK_API
    class Vec2
    {
    public:
        Vec2(N x, N y);
        
        N X;
        N Y;
    };

} // basilisk::math

#include "Vec2.tpp"

