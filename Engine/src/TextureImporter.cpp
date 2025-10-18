#include "TextureImporter.h"
#define STB_IMAGE_IMPLEMENTATION
#include <filesystem>

#include "stb_image.h"
#include "GL/glew.h"

namespace basilisk
{

    unsigned int TextureImporter::MakeTexture(const std::string& imageDir)
    {
        int width;
        int height;
        const auto data = ImportImage(imageDir, width, height);
        const auto texture = GenTexture(data, width, height);

        FreeImage(data);
        return texture;
    }

    unsigned char* TextureImporter::ImportImage(const std::string& imageDir, int& width, int& height)
    {
        int colorChannelsAmount;
        
        if (!std::filesystem::exists(imageDir))
        {
            throw ImageNotFound();
        }
        
        auto* data = stbi_load(imageDir.c_str(), &width, &height, &colorChannelsAmount, 0);

        if (!data)
            throw FailedTextureLoading();

        return data;
    }

    unsigned int TextureImporter::GenTexture(unsigned char* data, int &width, int& height)
    {
        unsigned int texture;

        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0); // check for glUniform1i to assign non default locations
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        return texture;
    }

    void TextureImporter::FreeImage(unsigned char* data)
    {
        if (!data)
            return;

        stbi_image_free(data);
    }

} // namespace basilisk
