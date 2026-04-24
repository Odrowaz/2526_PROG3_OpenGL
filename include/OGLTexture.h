#pragma once
#include <string>
#include <vitaGL.h>

class OGLTexture 
{
public:
    OGLTexture(const std::string& InImagePath, GLuint TextureSlotId = GL_TEXTURE0);
    OGLTexture(int Width, int Height, GLuint TextureSlotId = GL_TEXTURE0);
    ~OGLTexture();
    void Bind(GLuint TextureSlotId);
private:
    GLuint TextureId;
};