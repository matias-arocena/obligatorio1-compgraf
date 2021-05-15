#include "Texture.h"
#include "FreeImage.h"

#include <iostream>


Image Texture::loadImage(std::string file)
{
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(file.c_str());
    FIBITMAP* bitmap = FreeImage_Load(fif, file.c_str());
    bitmap = FreeImage_ConvertTo24Bits(bitmap);
    int width = FreeImage_GetWidth(bitmap);
    int height = FreeImage_GetHeight(bitmap);
    void* data = FreeImage_GetBits(bitmap);
    
    Image result;
    result.data = data;
    result.width = width;
    result.height = height;
    return result;
}

Texture::Texture(const std::string& filename)
{
    this->filename = filename;
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureId);
}


void Texture::load()
{
    Image image = loadImage(filename);
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
}
