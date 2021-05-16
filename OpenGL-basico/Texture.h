#pragma once
#include <string>
#include <SDL_opengl.h>
#include <vector>
#include <map>

struct Image {
    void* data;
    int height, width;
};

class Texture
{
    static std::map<std::string, GLuint> cache;
    std::string filename;
    GLuint textureId;
    Image loadImage(std::string file);

public:
    Texture(const std::string& filename);
    ~Texture();
    void load();
    void bind();
};

