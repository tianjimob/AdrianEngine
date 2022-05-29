#pragma once

#include "AdrianEngine/Input.h"
#include "Windows.h"
#include "aepch.h"

namespace AdrianEngine {
class WindowsInput : public Input {

protected:
  virtual bool isKeyPressedImpl(int keycode) override;
  virtual bool isMouseButtonPressedImpl(int button) override;
  virtual std::pair<float, float> getMousePositionImpl() override;
  virtual float getMouseXImpl() override;
  virtual float getMouseYImpl() override;

private:
};
} // namespace AdrianEngine