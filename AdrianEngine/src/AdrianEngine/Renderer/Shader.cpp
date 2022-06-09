#include "Shader.h"

#include <glad/glad.h>
#include <malloc.h>

#include <glm/gtc/type_ptr.hpp>

#include "AdrianEngine/Log.h"
namespace AdrianEngine {

enum class Shader::ShaderType : unsigned {
  FragmentShader = GL_FRAGMENT_SHADER,
  VertexShader = GL_VERTEX_SHADER
};

Shader::Shader(std::string_view vertexShader, std::string_view fragmentShader) {
  unsigned vs = compileShader(ShaderType::VertexShader, vertexShader);
  unsigned fs = compileShader(ShaderType::FragmentShader, fragmentShader);

  if (vs && fs) {
    m_rendererID = glCreateProgram();
    glAttachShader(m_rendererID, vs);
    glAttachShader(m_rendererID, fs);
    glLinkProgram(m_rendererID);

    int isLinked = 0;
    glGetProgramiv(m_rendererID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
      int length = 0;
      glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &length);
      auto *message = static_cast<char *>(alloca(length));
      glGetProgramInfoLog(m_rendererID, length, nullptr, message);
      glDeleteProgram(m_rendererID);
      AE_CORE_ERROR("[Link Error] {0}", message);
      AE_CORE_ASSERT(false, "failed link shader")
    }

    glDetachShader(m_rendererID, vs);
    glDetachShader(m_rendererID, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
  }
}

Shader::~Shader() { glDeleteProgram(m_rendererID); }

inline void Shader::bind() const { glUseProgram(m_rendererID); }

inline void Shader::unbind() const { glUseProgram(0); }

inline void Shader::setUniform(const std::string_view name, int value) {
  bind();
  glUniform1i(getUniform(name), value);
}

inline void Shader::setUniform(std::string_view name, float v1, float v2,
                               float v3, float v4) {
  bind();
  glUniform4f(getUniform(name), v1, v2, v3, v4);
}

inline void Shader::setUniform(std::string_view name, const glm::mat4 &matrix) {
  bind();
  glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

int32_t Shader::getUniform(std::string_view name) {
  if (auto uniform = m_uniforms.find(name); uniform != m_uniforms.end())
    return uniform->second;
  int32_t location = glGetUniformLocation(m_rendererID, name.data());
  m_uniforms[name] = location;
  return location;
}

unsigned Shader::compileShader(ShaderType type,
                               std::string_view shaderSource) const {
  unsigned id = glCreateShader(static_cast<unsigned>(type));
  const char *src = shaderSource.data();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int status = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    int length = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    auto *message = static_cast<char *>(alloca(length));
    glGetShaderInfoLog(id, length, nullptr, message);
    glDeleteShader(id);
    AE_CORE_ERROR("[Compile Error] {0}: {1}",
                  type == ShaderType::VertexShader ? "VertexShader: "
                                                   : "FragmentShader: ",
                  message);
    AE_CORE_ASSERT(false, "failed compile shader")
    return 0;
  }
  return id;
}
}  // namespace AdrianEngine