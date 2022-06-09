#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

#include "aepch.h"

namespace AdrianEngine {
inline void OpenGLRendererAPI::setClearColor(const glm::vec4& color) const {
  glClearColor(color.r, color.g, color.b, color.a);
}

inline void OpenGLRendererAPI::clear() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void OpenGLRendererAPI::drawIndexed(
    const std::shared_ptr<VertexArray>& vertexArray) const {
  glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->count(),
                 GL_UNSIGNED_INT, nullptr);
}
}  // namespace AdrianEngine