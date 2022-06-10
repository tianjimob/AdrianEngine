#include "WindowsWindow.h"

#include "AdrianEngine/Events/ApplicationEvent.h"
#include "AdrianEngine/Events/Event.h"
#include "AdrianEngine/Events/KeyEvent.h"
#include "AdrianEngine/Events/MouseEvent.h"
#include "AdrianEngine/Log.h"
#include "aepch.h"

namespace AdrianEngine {

static bool s_GLFWInitialized = false;

Window *Window::create(const WindowProps &props) {
  return new WindowsWindow{props};
}

WindowsWindow::WindowsWindow(const WindowProps &props) { init(props); }

WindowsWindow::~WindowsWindow() { shutdown(); }

void WindowsWindow::init(const WindowProps &props) {
  m_data.title = props.title;
  m_data.width = props.width;
  m_data.height = props.height;
  AE_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width,
               props.height);
  if (!s_GLFWInitialized) {
    /**
     * @todo glfwTerminate on system shutdown
     */
    int success = glfwInit();
    AE_CORE_ASSERT(success, "Couldn't initialize GLFW!");
    s_GLFWInitialized = true;
    glfwSetErrorCallback([](int error_code, const char *description) {
      AE_CORE_ERROR("[GLFW] Error Code {0}: {1}", error_code, description);
    });
  }

  m_window = glfwCreateWindow(props.width, props.height, m_data.title.c_str(),
                              nullptr, nullptr);
  m_context = new OpenGLContext(m_window);
  m_context->init();
  glfwSetWindowUserPointer(m_window, &m_data);
  setVSync(false);

  // Set GLFW callback
  glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int w, int h) {
    WindowData &data{
        *static_cast<WindowData *>(glfwGetWindowUserPointer(window))};
    data.width = w;
    data.height = h;
    WindowResizeEvent e{data.width, data.height};
    data.eventCallback(e);
  });

  glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
    const WindowData &data{
        *static_cast<WindowData *>(glfwGetWindowUserPointer(window))};
    WindowCloseEvent e;
    data.eventCallback(e);
  });

  glfwSetKeyCallback(
      m_window, [](GLFWwindow *window, int key, int, int action, int) {
        const WindowData &data{
            *static_cast<WindowData *>(glfwGetWindowUserPointer(window))};
        Event *e = nullptr;
        switch (action) {
          case GLFW_PRESS:
            e = new KeyPressedEvent(key, 0);
            break;
          case GLFW_RELEASE:
            e = new KeyReleasedEvent(key);
            break;
          case GLFW_REPEAT:
            e = new KeyPressedEvent(key, 1);
            break;
          default:
            break;
        }
        if (e) {
          data.eventCallback(*e);
          delete e;
        }
      });

  glfwSetCharCallback(m_window, [](GLFWwindow *window, unsigned int codepoint) {
    const WindowData &data{
        *static_cast<WindowData *>(glfwGetWindowUserPointer(window))};
    KeyTypedEvent e(codepoint);
    data.eventCallback(e);
  });

  glfwSetMouseButtonCallback(
      m_window, [](GLFWwindow *window, int button, int action, int) {
        const WindowData &data{
            *static_cast<WindowData *>(glfwGetWindowUserPointer(window))};
        Event *e = nullptr;
        switch (action) {
          case GLFW_PRESS:
            e = new MouseButtonPressedEvent(button);
            break;
          case GLFW_RELEASE:
            e = new MouseButtonReleasedEvent(button);
            break;
          default:
            break;
        }
        if (e) {
          data.eventCallback(*e);
          delete e;
        }
      });

  glfwSetScrollCallback(
      m_window, [](GLFWwindow *window, double xoffset, double yoffset) {
        const WindowData &data{
            *static_cast<WindowData *>(glfwGetWindowUserPointer(window))};
        MouseScrolledEvent e{static_cast<float>(xoffset),
                             static_cast<float>(yoffset)};
        data.eventCallback(e);
      });

  glfwSetCursorPosCallback(
      m_window, [](GLFWwindow *window, double xpos, double ypos) {
        const WindowData &data{
            *static_cast<WindowData *>(glfwGetWindowUserPointer(window))};
        MouseMovedEvent e{static_cast<float>(xpos), static_cast<float>(ypos)};
        data.eventCallback(e);
      });
}

void WindowsWindow::shutdown() { glfwDestroyWindow(m_window); }

void WindowsWindow::onUpdate() {
  glfwPollEvents();
  m_context->swapBuffers();
}

void WindowsWindow::setVSync(bool enabled) {
  if (enabled) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  m_data.vSync = enabled;
}

bool WindowsWindow::isVSync() const { return m_data.vSync; }

void *WindowsWindow::getNativeWindow() const {
  return static_cast<void *>(m_window);
}

}  // namespace AdrianEngine
