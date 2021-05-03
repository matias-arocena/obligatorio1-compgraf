#include "Texture.h"
#include "FreeImage.h"

#include <iostream>


Texture::Texture(const std::string& FileName)
{
    filename = FileName;
}


bool Texture::Load()
{
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filename.c_str());
    FIBITMAP* bitmap = FreeImage_Load(fif, filename.c_str());
    bitmap = FreeImage_ConvertTo24Bits(bitmap);
    int width = FreeImage_GetWidth(bitmap);
    int height = FreeImage_GetHeight(bitmap);
    void* data = FreeImage_GetBits(bitmap);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    return true;
}

void Texture::Bind(GLenum TextureUnit)
{
    glBindTexture(GL_TEXTURE_2D, textureId);
}
