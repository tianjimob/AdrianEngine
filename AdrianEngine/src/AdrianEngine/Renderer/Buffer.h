#pragma once

#include <stdint.h>

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Events/Event.h"
#include "aepch.h"

namespace AdrianEngine {

enum class ShaderDataType : std::uint8_t {
  None = 0,
  Float,
  Float2,
  Float3,
  Float4,
  Mat3,
  Mat4,
  Int,
  Int2,
  Int3,
  Int4,
  Bool
};

struct AE_API BufferElement {
  std::string_view name;
  ShaderDataType type;
  std::uint32_t size;
  std::uint32_t offset{0};
  bool normalized;

  BufferElement(ShaderDataType type, std::string_view name,
                bool normalized = false)
      : name(name), type(type), size(typeSize()), normalized(normalized) {}
  uint32_t count() const;
  uint32_t toOpenGL() const;

 private:
  uint32_t typeSize() const;
};

class AE_API BufferLayout {
 public:
  BufferLayout() = default;
  explicit BufferLayout(const std::initializer_list<BufferElement> &elements);
  const std::vector<BufferElement> &get() const;
  uint32_t stride() const;

  std::vector<BufferElement>::iterator begin();
  std::vector<BufferElement>::iterator end();
  std::vector<BufferElement>::const_iterator cbegin() const;
  std::vector<BufferElement>::const_iterator cend() const;

 private:
  std::vector<BufferElement> m_bufferElements;
  uint32_t m_stride{0};
};
class AE_API VertexBuffer {
 public:
  virtual ~VertexBuffer() = default;
  virtual void bind() const = 0;
  virtual void unbind() const = 0;
  virtual void setLayout(const BufferLayout &layout) = 0;
  virtual BufferLayout &getLayout() = 0;
  static VertexBuffer *create(float *vertices, std::uint32_t size);
};

class AE_API IndexBuffer {
 public:
  virtual ~IndexBuffer() = default;
  virtual void bind() const = 0;
  virtual void unbind() const = 0;
  static IndexBuffer *create(std::uint32_t *indices, std::uint32_t count);
};
}  // namespace AdrianEngine