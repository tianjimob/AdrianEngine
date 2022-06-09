#pragma once

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Renderer/Buffer.h"

namespace AdrianEngine {
class OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(float* vertices, std::uint32_t size);
  ~OpenGLVertexBuffer() override = default;
  void bind() const override;
  void unbind() const override;
  void setLayout(const BufferLayout& layout) override;
  BufferLayout& getLayout() override;

 private:
  std::uint32_t m_rendererID;
  BufferLayout m_layout;
};

class OpenGLIndexBuffer : public IndexBuffer {
 public:
  OpenGLIndexBuffer(std::uint32_t* indices, std::uint32_t count);
  ~OpenGLIndexBuffer() override = default;
  void bind() const override;
  void unbind() const override;
  uint32_t count() const override;

 private:
  uint32_t m_rendererID;
  uint32_t m_count;
};
}  // namespace AdrianEngine