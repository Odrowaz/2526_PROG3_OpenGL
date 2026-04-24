#pragma once
#include <string>
#include <glad/gl.h>
#include <glm/glm.hpp>

enum class EShaderInputType {
    POSUVNORM,
    POSUV,
};

struct VertexPinInfo {
  int location;
  int size;
  int stride;
  int offset;
};

struct XColor {
    float R;
    float G;
    float B;
    float A;
};

class OGLProgram
{
public:
    OGLProgram(const std::string& InVertexPath, const std::string& InFragmPath, EShaderInputType InInputType = EShaderInputType::POSUVNORM);
    ~OGLProgram();
    void Bind();
    void SetUniform(const std::string& InName, float InValue);
    void SetUniform(const std::string& InName, const XColor& InColor);
    void SetUniform(const std::string& InName, const glm::mat4& InMat);
    void SetUniform(const std::string& InName, const glm::vec3& InVector);
    EShaderInputType GetInputType() const { return InputType; }
private:
    GLuint ProgramId;
    EShaderInputType InputType;
};