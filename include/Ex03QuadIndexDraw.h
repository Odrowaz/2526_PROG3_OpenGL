#pragma once
#include <glad/gl.h>

class Ex03QuadIndexDraw 
{
public:
    Ex03QuadIndexDraw();
    ~Ex03QuadIndexDraw();
    void Update(float InDeltaTime);
private:
    class OGLProgram* Program;
    GLuint Vao;
    GLuint Vbo;
    GLuint Ebo;
};
