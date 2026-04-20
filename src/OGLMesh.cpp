#include "OGLMesh.h"
#include "ObjParser.h"

void OGLMesh::load(const std::vector<MeshPinInfo> &InPinInfo) {
  glGenVertexArrays(1, &Vao);
  glBindVertexArray(Vao);

  // 2. Create VBO to load data
  glGenBuffers(1, &Vbo);
  glBindBuffer(GL_ARRAY_BUFFER, Vbo);

  size_t DataSize = Vertices.size() * sizeof(float);
  glBufferData(GL_ARRAY_BUFFER, DataSize, Vertices.data(), GL_STATIC_DRAW);

  // 3. Link to Vertex Shader
  for (const auto &info : InPinInfo) {
    glVertexAttribPointer(info.location, info.size, GL_FLOAT, GL_FALSE,
                          info.stride * sizeof(float),
                          (void *)(info.offset * sizeof(float)));
    glEnableVertexAttribArray(info.location);
  }
}

OGLMesh::OGLMesh(const std::string InPath) {
  Obj Mesh;
  ObjParser::TryParse(InPath, Mesh);

  for (int Index = 0; Index < Mesh.triangles.size(); ++Index) {
    auto &triangle = Mesh.triangles[Index];

    Vertices.push_back(triangle.v1.point.x);
    Vertices.push_back(triangle.v1.point.y);
    Vertices.push_back(triangle.v1.point.z);
    Vertices.push_back(triangle.v1.uv.x);
    Vertices.push_back(triangle.v1.uv.y);
    Vertices.push_back(triangle.v1.normal.x);
    Vertices.push_back(triangle.v1.normal.y);
    Vertices.push_back(triangle.v1.normal.z);

    Vertices.push_back(triangle.v2.point.x);
    Vertices.push_back(triangle.v2.point.y);
    Vertices.push_back(triangle.v2.point.z);
    Vertices.push_back(triangle.v2.uv.x);
    Vertices.push_back(triangle.v2.uv.y);
    Vertices.push_back(triangle.v2.normal.x);
    Vertices.push_back(triangle.v2.normal.y);
    Vertices.push_back(triangle.v2.normal.z);

    Vertices.push_back(triangle.v3.point.x);
    Vertices.push_back(triangle.v3.point.y);
    Vertices.push_back(triangle.v3.point.z);
    Vertices.push_back(triangle.v3.uv.x);
    Vertices.push_back(triangle.v3.uv.y);
    Vertices.push_back(triangle.v3.normal.x);
    Vertices.push_back(triangle.v3.normal.y);
    Vertices.push_back(triangle.v3.normal.z);
  }

  VertexCount = Mesh.triangles.size() * 3;

  load({{0, 3, 8, 0}, {1, 2, 8, 3}, {2, 3, 8, 5}});
}

OGLMesh::OGLMesh(const std::vector<float> InVertices, int InVertexCount,
                 const std::vector<MeshPinInfo> &InPinInfo)
    : Vertices(InVertices), VertexCount(InVertexCount) {
  load(InPinInfo);
}

OGLMesh::~OGLMesh() {
  glDeleteVertexArrays(1, &Vao);
  glDeleteBuffers(1, &Vbo);
}

void OGLMesh::Bind() { glBindVertexArray(Vao); }

int OGLMesh::GetVertexCount() const { return VertexCount; }

void OGLMesh::Draw(const glm::mat4 &model, const glm::mat4 &mvp,
                   OGLProgram *program) {
  Bind();
  program->SetUniform("model", model);
  program->SetUniform("mvp", mvp);
  glDrawArrays(GL_TRIANGLES, 0, VertexCount);
};
