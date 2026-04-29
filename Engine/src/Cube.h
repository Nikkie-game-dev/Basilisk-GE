#pragma once
#include "Shape3D.h"

namespace basilisk
{
    class BASILISK_API Cube : Shape3D
    {
    protected:


    public:
        Cube(bool isSolid, const vec3& center, const vec3& size, const basilisk::Color& color);

    private:
        void SetVertices() override;
        void SetIndices() override;

    };
} // basilisk 
