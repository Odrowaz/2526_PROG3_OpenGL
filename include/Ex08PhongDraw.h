#pragma once
#include <vitaGL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    class OGLMesh* TrupMesh;
    class OGLMesh* CubeMesh;

    glm::mat4 View;
    glm::mat4 Projection;
    Camera Cam;
};
