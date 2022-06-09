#include "Shader.h"

#include <glad/glad.h>
#include <malloc.h>

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

void Shader::bind() const { glUseProgram(m_rendererID); }

void Shader::unbind() const { glUseProgram(0); }

void Shader::setUniform(const std::string_view name, int value) {
  glUniform1i(getUniform(name), value);
}

void Shader::setUniform(std::string_view name, float v1, float v2, float v3,
                        float v4) {
  glUniform4f(getUniform(name), v1, v2, v3, v4);
}

void Shader::setUniform(std::string_view name, const glm::mat4 &matrix) {
  glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::getUniform(std::string_view name) {
  if (auto uniform = m_uniforms.find(name); uniform != m_uniforms.end())
    return uniform->second;
  int location = glGetUniformLocation(m_rendererID, name.data());
  m_uniforms[name] = location;
  return location;
}

// Shader::ShaderSource Shader::parseShader(std::string_view path) const {
//   std::ifstream ifs(path.data());
//   std::stringstream ss;
//   ss << ifs.rdbuf();
//   ifs.close();
//   auto source = ss.str();
//   std::regex vertexRegex("^#shader vertex\\s+(#[^#]*)#end");
//   std::regex fragmentRegex("^#shader fragment\\s+(#[^#]*)#end");
//   std::smatch vertexMatch;
//   std::smatch fragmentMatch;
//   bool vSuccess = std::regex_search(source, vertexMatch, vertexRegex);
//   bool fSuccess = std::regex_search(source, fragmentMatch, fragmentRegex);
//   if (!vSuccess && !fSuccess) {
//     throw NotFound(
//         "[RegexSearch Error] VertexShader and FragmentShader Not Found!");
//   } else if (!vSuccess) {
//     throw NotFound("[RegexSearch Error] VertexShader not found!");
//   } else if (!fSuccess) {
//     throw NotFound("[RegexSearch Error] FragmentShader not found!");
//   }
//   return {vertexMatch[1], fragmentMatch[1]};
// }

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
                  type == ShaderType::FragmentShader ? "VertexShader: "
                                                     : "FragmentShader: ",
                  message);
    AE_CORE_ASSERT(false, "failed compile shader")
    return 0;
  }
  return id;
}
}  // namespace AdrianEngine