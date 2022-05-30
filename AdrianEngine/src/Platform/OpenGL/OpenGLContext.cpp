#include "OpenGLContext.h"
#include "AdrianEngine/Core.h"
#include "AdrianEngine/Log.h"
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
  AE_CORE_INFO("OpenGL Info:");
  AE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
  AE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
  AE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
}

void OpenGLContext::swapBuffers() { glfwSwapBuffers(m_windowHandle); }
} // namespace AdrianEngine