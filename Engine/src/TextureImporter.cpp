#include "TextureImporter.h"

#define STB_IMAGE_IMPLEMENTATION

#include <filesystem>

#include "GL/glew.h"
#include "Log.h"
#include "stb_image.h"

namespace basilisk
{
    
    TextureImporter::TextureData TextureImporter::MakeTextureData(const std::string& imageDir, Filters filter, FitMode fit)
    {
        int width;
        int height;
        int colorChannels;
        const auto data = ImportImage(imageDir, width, height, colorChannels);

        int channelType;

        switch (colorChannels)
        {
        case 1:
            channelType = GL_R;
            break;
        case 2:
            channelType = GL_RG;
            break;
        case 3:
            channelType = GL_RGB;
            break;
        case 4:
            channelType = GL_RGBA;
            break;
        default:
            channelType = GL_RGB;
            break;
        }

        const auto textureID = GenTexture(data, width, height, channelType, filter, fit);

        FreeImage(data);
        return {.textureID = textureID, .width = width, .height = height};
    }

    unsigned char* TextureImporter::ImportImage(const std::string& imageDir, int& width, int& height, int& outColorChannels)
    {
        Log::Get()->info("Loading Image at {}", imageDir);

        if (!std::filesystem::exists(imageDir))
        {
            Log::Get()->error("Image at {} not found", imageDir);
            return nullptr;
        }
        
        auto* data = stbi_load(imageDir.c_str(), &width, &height, &outColorChannels, 0);

        if (!data)
        {
            Log::Get()->error("Could not load data at {}", imageDir);
            return nullptr;        
        }

        return data;
    }

    unsigned int TextureImporter::GenTexture(unsigned char* data,
                                             int& width,
                                             int& height,
                                             const int format,
                                             const Filters& filter,
                                             const FitMode& fit)
    {
        Log::Get()->info("Generating texture");
        unsigned int texture;

        glGenTextures(1, &texture);

        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, texture);
        
        Log::Get()->info("Texture Id: {}", texture);

        SetFit(fit);
        SetFilter(filter);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        return texture;
    }

    void TextureImporter::SetFilter(const Filters& filter)
    {
        int minFilter = 0;
        int magFilter = 0;

        switch (filter)
        {
        case Filters::LINEAR:
            minFilter = GL_LINEAR;
            magFilter = minFilter;
            break;

        case Filters::MIPMAP_LINEAR:
            minFilter = GL_LINEAR_MIPMAP_LINEAR;
            magFilter = GL_LINEAR;
            break;

        case Filters::NEAREST:
            minFilter = GL_NEAREST;
            magFilter = minFilter;
            break;

        case Filters::MIPMAP_NEAREST:
            minFilter = GL_NEAREST_MIPMAP_NEAREST;
            magFilter = GL_NEAREST;
            break;
        }


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    }
    void TextureImporter::SetFit(const FitMode& fit)
    {
        int selectedFit = 0;

        switch (fit)
        {
        case FitMode::CLAMP_EDGE:
            selectedFit = GL_CLAMP_TO_EDGE;
            break;

        case FitMode::CLAMP_BORDER:
            selectedFit = GL_CLAMP_TO_BORDER;
            break;

        case FitMode::REPEAT:
            selectedFit = GL_REPEAT;
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, selectedFit);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, selectedFit);
    }

    void TextureImporter::BindTexture(const unsigned int texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void TextureImporter::UnbindTexture()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureImporter::FreeImage(unsigned char* data)
    {
        if (!data)
            return;

        stbi_image_free(data);
    }

} // namespace basilisk
