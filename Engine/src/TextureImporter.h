#pragma once
#include <string>
#include "Export.h"

namespace basilisk
{
    class BASILISK_API TextureImporter
    {
    public:
        /// <summary>
        /// Loads a texture to GPU from an image directory.
        /// </summary>
        /// <param name="imageDir">Relative path to image directory</param>
        /// <returns>Id of loaded texture</returns>
        static unsigned int GetTexture(std::string imageDir);

    private:
        static unsigned char* ImportImage(const std::string& imageDir, int& width, int& height);
        static unsigned int GenTexture(unsigned char* data, int& width, int& height);
        static void FreeImage(unsigned char* data);
    };

    class FailedTextureLoading : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Tried and failed to load a texture";
        }
    };
} // namespace basilisk
