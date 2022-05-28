#include "Application.h"

#include "AdrianEngine/Events/ApplicationEvent.h"
#include "AdrianEngine/Events/Event.h"
#include "AdrianEngine/Log.h"
#include "AdrianEngine/Window.h"
#include "aepch.h"
#include <functional>
#include <gl/GL.h>

namespace AdrianEngine {
Application::Application(/* args */) {
  m_window = std::unique_ptr<Window>(Window::create());
  m_window->setEventCallback(
      std::bind(&Application::onEvent, this, std::placeholders::_1));
}

Application::~Application() {}

void Application::run() {
  while (m_isRunning) {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    m_window->onUpdate();
  }
}

void Application::onEvent(Event &e) {
  EventDispatcher dispatcher{e};
  dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent &) {
    m_isRunning = false;
    return true;
  });
  AE_CORE_INFO("{0}", e.toString());
}
} // namespace AdrianEngine