#include "Application.h"

#include "AdrianEngine/Window.h"
#include "aepch.h"
#include <gl/GL.h>

namespace AdrianEngine {
Application::Application(/* args */)
{
    m_window  = std::unique_ptr<Window>(Window::create());
}

Application::~Application()
{
}

void Application::run()
{
    while (m_isRunning) {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        m_window->onUpdate();
    }
}
}