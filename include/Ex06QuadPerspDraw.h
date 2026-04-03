#pragma once
#include <glad/gl.h>

class Ex06QuadPerspDraw 
{
public:
    Ex06QuadPerspDraw();
    ~Ex06QuadPerspDraw();
    void Update(float InDeltaTime);
private:
    class OGLProgram* Program;
    GLuint Vao;
    GLuint Vbo;
    GLuint Ebo;
    class OGLTexture* BoxTexture;
};
