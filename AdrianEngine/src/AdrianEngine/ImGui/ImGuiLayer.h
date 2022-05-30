#pragma once

#include "AdrianEngine/Core.h"

#include "AdrianEngine/Events/ApplicationEvent.h"
#include "AdrianEngine/Events/KeyEvent.h"
#include "AdrianEngine/Events/MouseEvent.h"

#include "AdrianEngine/Layer.h"

namespace AdrianEngine {
class AE_API ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer();

  void onAttach() override;
  void onDetach() override;
  void onUpdate() override { /* don't need*/
  }
  void onEvent(Event &event) override { /* don't need*/
  }
  void onImGuiRender() override;

  void begin();
  void end();

private:
  bool onMouseButtonPressedEvent(MouseButtonPressedEvent &e);
  bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
  bool onMouseMovedEvent(MouseMovedEvent &e);
  bool onMouseScrolledEvent(MouseScrolledEvent &e);
  bool onKeyPressedEvent(KeyPressedEvent &e);
  bool onKeyReleasedEvent(KeyReleasedEvent &e);
  bool onKeyTypedEvent(KeyTypedEvent &e);
  bool onWindowResizeEvent(WindowResizeEvent &e);

private:
  float m_time = 0.0f;
};

} // namespace AdrianEngine