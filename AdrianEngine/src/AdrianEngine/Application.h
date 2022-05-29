#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "LayerStack.h"
#include "Window.h"
#include "aepch.h"

namespace AdrianEngine {
class AE_API Application {
public:
  Application();
  virtual ~Application();
  void run();

  void onEvent(Event &e);

  void pushLayer(Layer *layer);
  void pushOverlay(Layer *layer);

  inline static Application &get() { return *ms_instance; }
  inline Window &getWindow() { return *m_window; }

private:
  std::unique_ptr<Window> m_window;
  bool m_isRunning = true;
  LayerStack m_layerStack;
  static Application *ms_instance;
};

// to be defined in CLIENT
Application *createApplication();

} // namespace AdrianEngine
