#pragma once

#include "OGLMesh.h"
#include "OGLProgram.h"

class OGLPipeLine
{
private:
    GLuint Vao;
    GLuint Vbo;
    OGLProgram* Program;
    int VertexCount;
    void Link(OGLMesh &Mesh);
public:
    OGLPipeLine(OGLMesh& Mesh, OGLProgram* Program);
    ~OGLPipeLine();
    void Draw(const glm::mat4 &model, const glm::mat4 &mvp);

};