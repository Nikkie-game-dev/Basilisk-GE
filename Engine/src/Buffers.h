#pragma once
#include "Export.h"

struct BASILISK_API Buffers
{
    unsigned int Vbo = 0;
    unsigned int Vao = 0;
    unsigned int Ebo = 0;
    float* vertices = nullptr;
    unsigned int* indices = nullptr;
    int amountVertices;
    int amountIndices;
};
