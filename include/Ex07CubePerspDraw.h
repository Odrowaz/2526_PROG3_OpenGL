#pragma once
#include <glad/gl.h>

class Ex07CubePerspDraw 
{
public:
    Ex07CubePerspDraw();
    ~Ex07CubePerspDraw();
    void Update(float InDeltaTime);
private:
    class OGLProgram* Program;
    GLuint Vao;
    GLuint Vbo;
    class OGLTexture* BoxTexture;
};
