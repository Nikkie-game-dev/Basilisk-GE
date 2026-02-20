#pragma once
#include <filesystem>
#include <string>

#include "Export.h"

namespace basilisk
{
    enum class BASILISK_API Filters
    {
        LINEAR,
        MIPMAP_LINEAR,
        NEAREST,
        MIPMAP_NEAREST
    };

    enum class BASILISK_API FitMode
    {
        CLAMP_EDGE,
        CLAMP_BORDER,
        REPEAT
    };

    /// <summary>
    /// Static class for texture loading
    /// </summary>
    class BASILISK_API TextureImporter
    {
    public:

        struct TextureData
        {
            unsigned int textureID;
            int width;
            int height;
        };

        /// <summary>
        /// Loads a texture to GPU from an image directory.
        /// </summary>
        /// <param name="imageDir">Relative path to image directory</param>
        /// <param name="filter"></param>
        /// <param name="fit"></param>
        /// <returns>Data of the loaded texture.</returns>
        static TextureData MakeTextureData(const std::string& imageDir,
                                        Filters filter = Filters::LINEAR,
                                        FitMode fit = FitMode::REPEAT);

        /// <summary>
        /// Binds a texture for rendering.
        /// </summary>
        /// <param name="texture"></param>
        static void BindTexture(unsigned int texture);

        /// <summary>
        /// Unbinds the currently bound texture.
        /// </summary>
        static void UnbindTexture();

    private:
        static unsigned char* ImportImage(const std::string& imageDir, int& width, int& height, int& outColorChannels);
        static unsigned int GenTexture(unsigned char* data, int& width, int& height, int format, const Filters& filter, const FitMode& fit);
        static void SetFilter(const Filters& filter);
        static void SetFit(const FitMode& fit);
        static void FreeImage(unsigned char* data);
    };
    
} // namespace basilisk
