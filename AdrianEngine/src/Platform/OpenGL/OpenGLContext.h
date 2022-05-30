#pragma once

#include "AdrianEngine/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace AdrianEngine {
class OpenGLContext : public GraphicsContext {
public:
  explicit OpenGLContext(GLFWwindow *windowHandle);

  void init() override;
  void swapBuffers() override;

private:
  GLFWwindow *m_windowHandle;
};

} // namespace AdrianEngine