#pragma once

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Events/Event.h"
#include "AdrianEngine/Layer.h"

namespace AdrianEngine {
class AE_API ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer();

  void onAttach() override;
  void onDetach() override;
  void onUpdate() override;
  void onEvent(Event &event) override;

private:
  float m_time = 0.0f;
};

} // namespace AdrianEngine