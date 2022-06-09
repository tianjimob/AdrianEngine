#pragma once

#include <memory>

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Renderer/RendererAPI.h"
#include "AdrianEngine/Renderer/VertexArray.h"
#include "glm/glm.hpp"

namespace AdrianEngine {
class AE_API OpenGLRendererAPI : public RendererAPI {
 public:
  ~OpenGLRendererAPI() override = default;
  void setClearColor(const glm::vec4& color) const override;
  void clear() const override;
  void drawIndexed(
      const std::shared_ptr<VertexArray>& vertexArray) const override;
};
}  // namespace AdrianEngine