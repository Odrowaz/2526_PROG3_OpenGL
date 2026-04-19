#pragma once
#include "OGLProgram.h"
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <vector>

struct MeshPinInfo {
  int location;
  int size;
  int stride;
  int offset;
};

class OGLMesh {
private:
  GLuint Vao;
  GLuint Vbo;
  std::vector<float> Vertices;
  int VertexCount;

  void load(const std::vector<MeshPinInfo> &InPinInfo);

public:
  OGLMesh(const std::string InPath);

  OGLMesh(const std::vector<float> InVertices, int InVertexCount,
          const std::vector<MeshPinInfo> &InPinInfo);
  ~OGLMesh();

  void Bind();
  int GetVertexCount() const;
  void Draw(const glm::mat4 &model, const glm::mat4 &mvp, OGLProgram *program);
};