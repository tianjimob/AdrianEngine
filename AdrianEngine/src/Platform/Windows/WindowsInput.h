#pragma once

#include "AdrianEngine/Input.h"
#include "Windows.h"
#include "aepch.h"

namespace AdrianEngine {
class WindowsInput : public Input {
public:
  virtual ~WindowsInput() = default;

protected:
  bool isKeyPressedImpl(int keycode) override;
  bool isMouseButtonPressedImpl(int button) override;
  std::pair<float, float> getMousePositionImpl() override;
  float getMouseXImpl() override;
  float getMouseYImpl() override;
};
} // namespace AdrianEngine