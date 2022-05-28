#include "WindowsWindow.h"

#include "aepch.h"

namespace AdrianEngine {
static bool s_GLFWInitialized = false;
Window* Window::create(const WindowProps& props)
{
    return new WindowsWindow { props };
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
    init(props);
}

WindowsWindow::~WindowsWindow()
{
    shutdown();
}

void WindowsWindow::init(const WindowProps& props)
{
    m_data.title = props.title;
    m_data.width = props.width;
    m_data.height = props.height;
    AE_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);
    if (!s_GLFWInitialized) {
        /**
         * @todo glfwTerminate on system shutdown
         */
        int success = glfwInit();
        AE_CORE_ASSERT(success, "Couldn't initialize GLFW!");
        s_GLFWInitialized = true;
    }

    m_window = glfwCreateWindow(props.width, props.height, m_data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_data);
    setVSync(true);
}

void WindowsWindow::shutdown()
{
    glfwDestroyWindow(m_window);
}

void WindowsWindow::onUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

void WindowsWindow::setVSync(bool enabled)
{
    if (enabled) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
    m_data.vSync = enabled;
}

bool WindowsWindow::isVSync() const
{
    return m_data.vSync;
}

} // namespace AdrianEngine
