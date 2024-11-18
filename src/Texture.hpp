#pragma once

#include <glad/glad.h>


class Texture
{

public:
    Texture();
    Texture(const char* fileLocation);
    ~Texture();

    bool LoadTexture();
    bool LoadTextureA();
    void UseTexture();
    void ClearTexture();


private:
    GLuint textureID;
    int width, height, bitDepth;

    const char* filepath;
    
};