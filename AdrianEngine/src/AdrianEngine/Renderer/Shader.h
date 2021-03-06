#pragma once

#include <glm/glm.hpp>

#include "AdrianEngine/Core.h"
#include "aepch.h"
namespace AdrianEngine {
class AE_API Shader {
 public:
  Shader(std::string_view vertexShader, std::string_view fragmentShader);
  ~Shader();

  void bind() const;
  void unbind() const;

  void setUniform(const std::string_view name, int value);
  void setUniform(std::string_view name, float v1, float v2, float v3,
                  float v4);
  void setUniform(std::string_view name, const glm::mat4& matrix);

  int32_t getUniform(std::string_view name);

 private:
  unsigned m_rendererID{0};
  std::unordered_map<std::string_view, unsigned> m_uniforms;

  enum class ShaderType : unsigned;
  unsigned compileShader(ShaderType type, std::string_view shaderSource) const;
};
}  // namespace AdrianEngine
