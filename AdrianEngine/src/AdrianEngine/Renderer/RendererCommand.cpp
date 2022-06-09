#include "RendererCommand.h"

#include "AdrianEngine/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "aepch.h"

namespace AdrianEngine {
inline void RendererCommand::setClearColor(const glm::vec4& color) {
  ms_rendererAPI->setClearColor(color);
}

inline void RendererCommand::clear() { ms_rendererAPI->clear(); }

inline void RendererCommand::drawIndexed(
    const std::shared_ptr<VertexArray>& vertexArray) {
  ms_rendererAPI->drawIndexed(vertexArray);
}
#ifdef AE_PLATFORM_WINDOWS
RendererAPI* RendererCommand::ms_rendererAPI = new OpenGLRendererAPI;
#endif
}  // namespace AdrianEngine