#include "OpenGLContext.h"
#include "AdrianEngine/Core.h"
#include <glad/glad.h>

namespace AdrianEngine {
OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : m_windowHandle(windowHandle) {
  AE_CORE_ASSERT(m_windowHandle, "Window handle is null");
}

void OpenGLContext::init() {
  glfwMakeContextCurrent(m_windowHandle);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  AE_CORE_ASSERT(status, "Faild to intialized Glad!");
}

void OpenGLContext::swapBuffers() { glfwSwapBuffers(m_windowHandle); }
} // namespace AdrianEngine