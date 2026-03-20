#pragma once
#include <glad/gl.h>

class Ex01TriangleDraw 
{
public:
    Ex01TriangleDraw();
    ~Ex01TriangleDraw();
    void Update(float InDeltaTime);
private:
    GLuint ProgramId;
    GLuint Vao;
    GLuint Vbo;
};
