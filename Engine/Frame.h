#pragma once
class Frame
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
