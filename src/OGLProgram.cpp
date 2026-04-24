#include "OGLProgram.h"
#include <fstream>
#include <iostream>
#include <vector>


static std::string ReadFile(const std::string &InPath);
static GLuint CreateShader(const std::string &InPath, GLuint InShaderType);
static GLint CreateProgram(GLuint VertexShaderId, GLuint FragmentShaderId);

OGLProgram::OGLProgram(const std::string &InVertexPath,
                       const std::string &InFragmPath) {
  GLuint VertexShaderId = CreateShader(InVertexPath, GL_VERTEX_SHADER);
  GLuint FragmentShaderId = CreateShader(InFragmPath, GL_FRAGMENT_SHADER);
  ProgramId = CreateProgram(VertexShaderId, FragmentShaderId);
}

OGLProgram::~OGLProgram() { glDeleteProgram(ProgramId); }

void OGLProgram::Bind() { glUseProgram(ProgramId); }

void OGLProgram::SetUniform(const std::string &InName, float InValue) {
  glUniform1f(glGetUniformLocation(ProgramId, InName.c_str()), InValue);
}

void OGLProgram::SetUniform(const std::string &InName, int InValue) {
  glUniform1i(glGetUniformLocation(ProgramId, InName.c_str()), InValue);
}

void OGLProgram::SetUniform(const std::string &InName, const XColor &InColor) {
  glUniform4fv(glGetUniformLocation(ProgramId, InName.c_str()), 1,
               reinterpret_cast<const GLfloat *>(&InColor));
}

void OGLProgram::SetUniform(const std::string &InName,
                            const glm::mat4 &InMatrix) {
  glUniformMatrix4fv(glGetUniformLocation(ProgramId, InName.c_str()), 1,
                     GL_FALSE, &InMatrix[0][0]);
}

void OGLProgram::SetUniform(const std::string &InName,
                            const glm::vec3 &InVector) {
  glUniform3fv(glGetUniformLocation(ProgramId, InName.c_str()), 1,
               &InVector[0]);
}

std::string ReadFile(const std::string &InPath) {
  std::ifstream InputStream(InPath, std::ios::ate);
  size_t FileSize = InputStream.tellg(); // cursor position in bytes

  std::string Text;
  Text.resize(FileSize);

  InputStream.seekg(0, std::ios::beg);
  InputStream.read(&Text[0], FileSize);

  InputStream.close();
  return Text;
}

GLuint CreateShader(const std::string &InPath, GLuint InShaderType) {
  std::string Text = ReadFile(InPath);
  const char *ShaderSource = Text.c_str();

  GLuint ShaderId = glCreateShader(InShaderType);
  glShaderSource(ShaderId, 1, &ShaderSource, NULL);
  glCompileShader(ShaderId);

  return ShaderId;
}

GLint CreateProgram(GLuint VertexShaderId, GLuint FragmentShaderId) {
  GLuint ProgramId = glCreateProgram();
  glAttachShader(ProgramId, VertexShaderId);
  glAttachShader(ProgramId, FragmentShaderId);
  glBindAttribLocation(ProgramId, 0, "vert_pos");
  glBindAttribLocation(ProgramId, 1, "vert_uv");
  glBindAttribLocation(ProgramId, 2, "vert_norm");
  glLinkProgram(ProgramId);

  return ProgramId;
}
