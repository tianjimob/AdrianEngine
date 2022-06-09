#pragma once

#include <memory>
#include <vector>

#include "AdrianEngine/Core.h"
#include "Buffer.h"

namespace AdrianEngine {
class AE_API VertexArray {
 public:
  virtual ~VertexArray() = default;
  virtual void bind() const = 0;
  virtual void unbind() const = 0;
  virtual void addVertexBuffer(
      const std::shared_ptr<VertexBuffer> &vertexBuffer) = 0;
  virtual void setIndexBuffer(
      const std::shared_ptr<IndexBuffer> &indexBuffer) = 0;
  virtual const std::vector<std::shared_ptr<VertexBuffer>>
      &getVertexBuffers() = 0;
  virtual const std::shared_ptr<IndexBuffer> &getIndexBuffer() = 0;
  static VertexArray *create();
};
}  // namespace AdrianEngine