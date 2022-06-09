#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace AdrianEngine {
VertexArray *VertexArray::create() {
#ifdef AE_PLATFORM_WINDOWS
  return new OpenGLVertexArray;
#endif
}
}  // namespace AdrianEngine