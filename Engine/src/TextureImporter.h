#pragma once
#include <filesystem>
#include <string>
#include "Export.h"

namespace basilisk
{
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
        /// <returns>Id of loaded texture</returns>
        static unsigned int MakeTexture(const std::string& imageDir);

    private:
        static void LoadTexture();
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
