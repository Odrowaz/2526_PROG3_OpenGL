#include "OGLMesh.h"
#include "ObjParser.h"

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

  InputType = EShaderInputType::POSUVNORM;
}

OGLMesh::OGLMesh(const std::vector<float> InVertices, int InVertexCount,
                 EShaderInputType InInputType)
    : Vertices(InVertices), VertexCount(InVertexCount), InputType(InInputType) {
}

int OGLMesh::GetVertexCount() const { return VertexCount; }

