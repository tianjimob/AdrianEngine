#include "Renderer.h"

#include "AdrianEngine/Renderer/RendererCommand.h"
#include "aepch.h"

namespace AdrianEngine {
Renderer::SceneData* Renderer::ms_sceneData = new Renderer::SceneData;
void Renderer::beginScene(const OrthographicCamera& camera) {
  ms_sceneData->viewProjection = camera.getViewProjection();
}

void Renderer::endScene() {}

void Renderer::submit(const std::shared_ptr<Shader>& shader,
                      const std::shared_ptr<VertexArray>& vertexArray) {
  shader->bind();
  shader->setUniform("u_ViewProjection", ms_sceneData->viewProjection);
  vertexArray->bind();
  RendererCommand::drawIndexed(vertexArray);
}
}  // namespace AdrianEngine