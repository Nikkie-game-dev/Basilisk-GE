#pragma once
#include "Export.h"

namespace basilisk
{
    struct BASILISK_API Buffers
    {
        unsigned int Vbo = 0;
        unsigned int Vao = 0;
        unsigned int Ebo = 0;
        float* Vertices = nullptr;
        unsigned int* Indices = nullptr;
        int AmountVertices;
        int AmountIndices;
    };
}
