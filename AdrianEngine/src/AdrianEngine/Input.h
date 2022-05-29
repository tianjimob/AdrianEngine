#pragma once

#include "Core.h"
#include "aepch.h"

namespace AdrianEngine {
class AE_API Input {
public:
  inline static bool isKeyPressed(int keycode) {
    return ms_instance->isKeyPressedImpl(keycode);
  }
  inline static bool isMouseButtonPressed(int button) {
    return ms_instance->isMouseButtonPressedImpl(button);
  }
  inline static std::pair<float, float> getMousePosition() {
    return ms_instance->getMousePositionImpl();
  }
  inline static float getMouseX() { return ms_instance->getMouseXImpl(); }
  inline static float getMouseY() { return ms_instance->getMouseYImpl(); }

protected:
  virtual bool isKeyPressedImpl(int keycode) = 0;
  virtual bool isMouseButtonPressedImpl(int button) = 0;
  virtual std::pair<float, float> getMousePositionImpl() = 0;
  virtual float getMouseXImpl() = 0;
  virtual float getMouseYImpl() = 0;

private:
  static Input *ms_instance;
};
} // namespace AdrianEngine