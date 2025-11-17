#pragma once
#include "Export.h"

namespace basilisk
{
    
    struct BASILISK_API Buffers
    {
        /// <summary>
        /// Vertex Buffer Object. Stores vertex data.
        /// </summary>
        unsigned int Vbo = 0;

        /// <summary>
        /// Vertex Array Object. Stores all the attributes needed to supply vertex data 
        /// </summary>
        unsigned int Vao = 0;

        /// <summary>
        /// Element Buffer Object. Stores indices.
        /// </summary>
        unsigned int Ebo = 0;

        /// <summary>
        /// Pointer to an array of vertices.
        /// </summary>
        float* Vertices = nullptr;

        /// <summary>
        /// Pointer to an array of indices.
        /// </summary>
        unsigned int* Indices = nullptr;

        /// <summary>
        /// Amount of vertices.
        /// </summary>
        int AmountVertices;

        /// <summary>
        /// Amount of indices.
        /// </summary>
        int AmountIndices;
    };
}
