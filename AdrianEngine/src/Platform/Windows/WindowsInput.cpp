#include "WindowsInput.h"
#include "AdrianEngine/Application.h"
#include "AdrianEngine/Input.h"
#include "AdrianEngine/Window.h"
#include <GLFW/glfw3.h>

namespace AdrianEngine {
Input *Input::ms_instance = new WindowsInput;

bool WindowsInput::isKeyPressedImpl(int keycode) {
  auto *window = static_cast<GLFWwindow *>(
      Application::get().getWindow().getNativeWindow());
  return glfwGetKey(window, keycode) == GLFW_PRESS;
}

bool WindowsInput::isMouseButtonPressedImpl(int button) {
  auto *window = static_cast<GLFWwindow *>(
      Application::get().getWindow().getNativeWindow());
  return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::getMousePositionImpl() {
  auto *window = static_cast<GLFWwindow *>(
      Application::get().getWindow().getNativeWindow());
  double x;
  double y;
  glfwGetCursorPos(window, &x, &y);
  return {static_cast<float>(x), static_cast<float>(y)};
}

float WindowsInput::getMouseXImpl() { return getMousePositionImpl().first; }

float WindowsInput::getMouseYImpl() { return getMousePositionImpl().second; }
} // namespace AdrianEngine