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
        /// <summary>
        /// Loads a texture to GPU from an image directory.
        /// </summary>
        /// <param name="imageDir">Relative path to image directory</param>
        /// <param name="filter"></param>
        /// <param name="fit"></param>
        /// <returns>Id of loaded texture</returns>
        static unsigned int MakeTexture(const std::string& imageDir, Filters filter = Filters::LINEAR, FitMode fit = FitMode::REPEAT);
        
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
        static unsigned int GenTexture(unsigned char* data,
                                       int& width,
                                       int& height,
                                       int format,
                                       Filters filter,
                                       FitMode fit);
        static void SetFilter(Filters filter);
        static void SetFit(FitMode);
        static void FreeImage(unsigned char* data);
    };

    /// <summary>
    /// Exception for failed texture loading.
    /// </summary>
    class FailedTextureLoading : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            return "Tried and failed to load a texture";
        }
    };

    /// <summary>
    /// Exception for when the image is not found in the directory.
    /// </summary>
    class ImageNotFound : std::exception
    {
    public:
        [[nodiscard]] char const* what() const override
        {
            std::string error = "Image has not been found, files the Engine can see: ";
            for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
                error += entry.path().string();

            return error.c_str();
        }
    };
} // namespace basilisk
