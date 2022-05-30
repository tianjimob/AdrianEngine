#pragma once

#include "AdrianEngine/Window.h"
#include <GLFW/glfw3.h>

namespace AdrianEngine {
class WindowsWindow : public Window {

public:
  explicit WindowsWindow(const WindowProps &props);
  ~WindowsWindow() override;

  void onUpdate() override;

  inline unsigned int getWidth() const override { return m_data.width; }
  inline unsigned int getHeight() const override { return m_data.height; }

  // Window attributes
  inline void setEventCallback(const EventCallback &callback) override {
    m_data.eventCallback = callback;
  }
  void setVSync(bool enabled) override;
  bool isVSync() const override;

  inline void *getNativeWindow() const override;

private:
  void init(const WindowProps &props);
  void shutdown();

  GLFWwindow *m_window;
  struct WindowData {
    std::string title;
    unsigned width;
    unsigned height;
    bool vSync;
    EventCallback eventCallback;
  };
  WindowData m_data;
};
} // namespace AdrianEngine
