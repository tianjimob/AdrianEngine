#include "Renderer.h"

#include "AdrianEngine/Renderer/RendererCommand.h"
#include "aepch.h"

namespace AdrianEngine {
void Renderer::beginScene() {}

void Renderer::endScene() {}

void Renderer::submit(const std::shared_ptr<VertexArray> &vertexArray) {
  vertexArray->bind();
  RendererCommand::drawIndexed(vertexArray);
}
}  // namespace AdrianEngine