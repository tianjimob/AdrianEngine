#pragma once

#include <memory>

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Renderer/VertexArray.h"
#include "RendererAPI.h"
#include "glm/glm.hpp"

namespace AdrianEngine {
class AE_API RendererCommand {
 public:
  static void setClearColor(const glm::vec4& color);
  static void clear();
  static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

 private:
  static RendererAPI* ms_rendererAPI;
};
}  // namespace AdrianEngine