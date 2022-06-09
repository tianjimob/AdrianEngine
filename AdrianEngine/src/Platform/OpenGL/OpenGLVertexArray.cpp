#include "OpenGLVertexArray.h"

#include <glad/glad.h>

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Renderer/Buffer.h"
#include "AdrianEngine/Renderer/VertexArray.h"
namespace AdrianEngine {
OpenGLVertexArray::OpenGLVertexArray() { glGenVertexArrays(1, &m_rendererID); }

OpenGLVertexArray::~OpenGLVertexArray() {
  glDeleteVertexArrays(1, &m_rendererID);
}

inline void OpenGLVertexArray::bind() const { glBindVertexArray(m_rendererID); }

inline void OpenGLVertexArray::unbind() const { glBindVertexArray(0); }

void OpenGLVertexArray::addVertexBuffer(
    const std::shared_ptr<VertexBuffer>& vertexBuffer) {
  AE_CORE_ASSERT(vertexBuffer->getLayout().get().size(),
                 "VertexBuffer has no layout");

  glBindVertexArray(m_rendererID);
  vertexBuffer->bind();

  int index = 0;
  uint32_t stride = vertexBuffer->getLayout().stride();
  for (const auto& elem : vertexBuffer->getLayout()) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, elem.count(), elem.toOpenGL(),
                          elem.normalized ? GL_TRUE : GL_FALSE, stride,
                          (const void*)elem.offset);
    ++index;
  }

  m_vertexBuffers.push_back(vertexBuffer);
}

inline void OpenGLVertexArray::setIndexBuffer(
    const std::shared_ptr<IndexBuffer>& indexBuffer) {
  glBindVertexArray(m_rendererID);
  indexBuffer->bind();
  m_indexBuffer = indexBuffer;
}

inline const std::vector<std::shared_ptr<VertexBuffer>>&
OpenGLVertexArray::getVertexBuffers() {
  return m_vertexBuffers;
}

inline const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::getIndexBuffer() {
  return m_indexBuffer;
}
}  // namespace AdrianEngine