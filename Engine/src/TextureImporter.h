#pragma once
#include <string>
#include "Export.h"

namespace basilisk
{
    class BASILISK_API TextureImporter
    {
    public:
        TextureImporter();
        static unsigned int GetTexture(std::string imageDir);

    private:
        unsigned char* ImportImage(std::string imageDir, int& width, int& height);
        unsigned int GenTexture(unsigned char* data, int& width, int& height);
        void FreeImage(unsigned char* data);
    };

    class FailedTextureLoading : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Tried and failed load a texture";
        }
    };
} // namespace basilisk
