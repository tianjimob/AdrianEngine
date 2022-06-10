#pragma once
#include <memory>

#include "AdrianEngine/Core/Timestep.h"
#include "Core.h"
#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Window.h"
#include "aepch.h"

namespace AdrianEngine {
class AE_API Application {
 public:
  Application();
  virtual ~Application() = default;
  void run();

  void onEvent(Event &e);

  void pushLayer(Layer *layer);
  void pushOverlay(Layer *layer);

  inline static Application &get() { return *ms_instance; }
  inline Window &getWindow() { return *m_window; }

 private:
  std::unique_ptr<Window> m_window;
  ImGuiLayer *m_imGuiLayer;
  bool m_isRunning{true};
  LayerStack m_layerStack;
  Timestep m_timestep;
  static Application *ms_instance;
};

// to be defined in CLIENT
Application *createApplication();

}  // namespace AdrianEngine
