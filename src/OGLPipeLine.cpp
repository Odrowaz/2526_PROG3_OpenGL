#include "OGLPipeLine.h"
#include "OGLMesh.h"
#include <stdexcept>
#include <vector>

static std::vector<VertexPinInfo> BuildPinInfo(EShaderInputType programInput,
                                               EShaderInputType meshInput) {
  if (programInput == EShaderInputType::POSUV) {
    if (meshInput == EShaderInputType::POSUV) {
      return {{0, 3, 5, 0}, {1, 2, 5, 3}};
    }
    if (meshInput == EShaderInputType::POSUVNORM) {
      return {{0, 3, 8, 0}, {1, 2, 8, 3}};
    }
  } else if (programInput == EShaderInputType::POSUVNORM &&
             meshInput == EShaderInputType::POSUVNORM) {
    return {{0, 3, 8, 0}, {1, 2, 8, 3}, {2, 3, 8, 5}};
  }

  throw std::runtime_error(
      "Unsupported mesh input type for the given shader input type");
}

OGLPipeLine::OGLPipeLine(OGLMesh &Mesh, OGLProgram *Program)
    : Program(Program), VertexCount(Mesh.GetVertexCount()) {
  glGenVertexArrays(1, &Vao);
  glBindVertexArray(Vao);

  // 2. Create VBO to load data
  glGenBuffers(1, &Vbo);
  glBindBuffer(GL_ARRAY_BUFFER, Vbo);

  size_t DataSize = Mesh.GetVerticesSize();
  glBufferData(GL_ARRAY_BUFFER, DataSize, Mesh.GetVertices(), GL_STATIC_DRAW);
  Link(Mesh);
}

OGLPipeLine::~OGLPipeLine() {
  glDeleteBuffers(1, &Vbo);
  glDeleteVertexArrays(1, &Vao);
}

void OGLPipeLine::Link(OGLMesh &Mesh) {
  const std::vector<VertexPinInfo> InPinInfo =
      BuildPinInfo(Program->GetInputType(), Mesh.GetInputType());

  for (const auto &info : InPinInfo) {
    glVertexAttribPointer(info.location, info.size, GL_FLOAT, GL_FALSE,
                          info.stride * sizeof(float),
                          (void *)(info.offset * sizeof(float)));
    glEnableVertexAttribArray(info.location);
  }
}

void OGLPipeLine::Draw(const glm::mat4 &model, const glm::mat4 &mvp) {
  glBindVertexArray(Vao);
  Program->Bind();
  Program->SetUniform("model", model);
  Program->SetUniform("mvp", mvp);
  glDrawArrays(GL_TRIANGLES, 0, VertexCount);
};