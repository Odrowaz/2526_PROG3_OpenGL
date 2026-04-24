#pragma once
#include "OGLProgram.h"
#include <cstddef>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <vector>


class OGLMesh {
private:

  std::vector<float> Vertices;
  int VertexCount;
  EShaderInputType InputType;

public:
  OGLMesh(const std::string InPath);

  OGLMesh(const std::vector<float> InVertices, int InVertexCount,
          EShaderInputType InInputType = EShaderInputType::POSUVNORM);
  void Bind();
  int GetVertexCount() const;
  float* GetVertices() { return Vertices.data(); }
  size_t GetVerticesSize() const { return Vertices.size() * sizeof(float); }
  EShaderInputType GetInputType() const { return InputType; }
};