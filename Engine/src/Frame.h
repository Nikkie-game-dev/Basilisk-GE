#pragma once

#include "Export.h"

namespace basilisk
{
    class BASILISK_API Frame
    {
        struct UVCoords
        {
            float u;
            float v;
        };

    public:
        Frame() = default;
        ~Frame() = default;
        UVCoords coords[4];
    };

} // namespace basilisk
