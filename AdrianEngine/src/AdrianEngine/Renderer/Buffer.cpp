#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace AdrianEngine {

uint32_t BufferElement::count() const {
  static std::array count{
      0,                   // None
      1,     2,     3, 4,  // Float*
      3 * 3, 4 * 4,        // Mat*
      1,     2,     3, 4,  // Int*
      1                    // Bool
  };
  return count[static_cast<uint8_t>(type)];
}

uint32_t BufferElement::typeSize() const {
  static std::array size{
      0,                                   // None
      4,         4 * 2,     4 * 3, 4 * 4,  // Float*
      4 * 3 * 3, 4 * 4 * 4,                // Mat*
      4,         4 * 2,     4 * 3, 4 * 4,  // Int*
      4                                    // Bool
  };
  return size[static_cast<uint8_t>(type)];
}

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
    : m_bufferElements{elements} {
  for (auto& elem : m_bufferElements) {
    elem.offset = m_stride;
    m_stride += elem.size;
  }
}

const std::vector<BufferElement>& BufferLayout::get() const {
  return m_bufferElements;
}

uint32_t BufferLayout::stride() const { return m_stride; }

std::vector<BufferElement>::iterator BufferLayout::begin() {
  return m_bufferElements.begin();
}

std::vector<BufferElement>::iterator BufferLayout::end() {
  return m_bufferElements.end();
}

std::vector<BufferElement>::const_iterator BufferLayout::cbegin() const {
  return m_bufferElements.cbegin();
}

std::vector<BufferElement>::const_iterator BufferLayout::cend() const {
  return m_bufferElements.cend();
}

VertexBuffer* VertexBuffer::create(float* vertices, std::uint32_t size) {
#ifdef AE_PLATFORM_WINDOWS
  return new OpenGLVertexBuffer{vertices, size};
#endif
}

IndexBuffer* IndexBuffer::create(std::uint32_t* indices, std::uint32_t count) {
#ifdef AE_PLATFORM_WINDOWS
  return new OpenGLIndexBuffer{indices, count};
#endif
}
}  // namespace AdrianEngine