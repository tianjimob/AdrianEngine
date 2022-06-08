#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace AdrianEngine {
OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, std::uint32_t size) {
  glGenBuffers(1, &m_rendererID);
  glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void OpenGLVertexBuffer::bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void OpenGLVertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void OpenGLVertexBuffer::setLayout(const BufferLayout& layout) {
  m_layout = layout;
}

BufferLayout& OpenGLVertexBuffer::getLayout() { return m_layout; }

OpenGLIndexBuffer::OpenGLIndexBuffer(std::uint32_t* indices,
                                     std::uint32_t count) {
  glGenBuffers(1, &m_rendererID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(std::uint32_t), indices,
               GL_STATIC_DRAW);
}

void OpenGLIndexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void OpenGLIndexBuffer::unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}  // namespace AdrianEngine