#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Renderer/VertexArray.h"
#include "glm/glm.hpp"

namespace AdrianEngine {
class AE_API RendererAPI {
 public:
  enum class API { None = 0, OpenGL = 1 };
  virtual ~RendererAPI() = default;
  virtual void setClearColor(const glm::vec4& color) const = 0;
  virtual void clear() const = 0;
  virtual void drawIndexed(
      const std::shared_ptr<VertexArray>& vertexArray) const = 0;
  static API getAPI();

 private:
#ifdef AE_PLATFORM_WINDOWS
  static const API ms_api = API::OpenGL;
#endif
};
}  // namespace AdrianEngine