#pragma once

#include <memory>

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Renderer/VertexArray.h"

namespace AdrianEngine {
class AE_API Renderer {
 public:
  static void beginScene();
  static void endScene();
  static void submit(const std::shared_ptr<VertexArray>& vertexArray);
};
}  // namespace AdrianEngine