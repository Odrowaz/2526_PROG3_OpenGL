#pragma once
#include "OGLPipeLine.h"
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct Camera
{
    glm::vec3 Position;
    glm::vec3 Direction;
    glm::vec3 Up;
    float FovY;
    float AspectRatio;
    float ZNear;
    float ZFar;
} typedef Camera;

class Ex08PhongDraw 
{
public:
    Ex08PhongDraw();
    ~Ex08PhongDraw();
    void Update(float InDeltaTime);
private:
    class OGLProgram* TrupProgram;
    class OGLProgram* CubeProgram;
    class OGLTexture* TrupTexture;
    class OGLTexture* CubeTexture;
    class OGLPipeLine* TrupPipeLine;
    class OGLPipeLine* CubePipeLine;

    glm::mat4 View;
    glm::mat4 Projection;
    Camera Cam;
};
