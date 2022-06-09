#pragma once

#include "AdrianEngine/Renderer/Buffer.h"
#include "AdrianEngine/Renderer/VertexArray.h"
#include "aepch.h"

namespace AdrianEngine {
class OpenGLVertexArray : public VertexArray {
 public:
  OpenGLVertexArray();
  ~OpenGLVertexArray() override;
  void bind() const override;
  void unbind() const override;
  void addVertexBuffer(
      const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
  void setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;
  const std::vector<std::shared_ptr<VertexBuffer>> &getVertexBuffers();
  const std::shared_ptr<IndexBuffer> &getIndexBuffer();

 private:
  uint32_t m_rendererID;
  std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
  std::shared_ptr<IndexBuffer> m_indexBuffer;
};

}  // namespace AdrianEngine