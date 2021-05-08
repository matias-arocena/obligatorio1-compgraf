#pragma once
#include <string>
#include <SDL_opengl.h>

class Texture
{
    std::string filename;
    GLuint textureId;

public:
    Texture(const std::string& FileName);
    ~Texture();
    bool load();
    void bind();
};

