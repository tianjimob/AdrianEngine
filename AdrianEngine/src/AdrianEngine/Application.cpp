#include "Application.h"

#include <chrono>
#include <ratio>
#include <thread>

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Events/ApplicationEvent.h"
#include "AdrianEngine/Events/Event.h"
#include "AdrianEngine/ImGui/ImGuiLayer.h"
#include "AdrianEngine/Log.h"
#include "AdrianEngine/Renderer/Buffer.h"
#include "AdrianEngine/Renderer/Renderer.h"
#include "AdrianEngine/Renderer/RendererCommand.h"
#include "AdrianEngine/Renderer/Shader.h"
#include "AdrianEngine/Renderer/VertexArray.h"
#include "AdrianEngine/Window.h"
#include "Input.h"
#include "aepch.h"

struct Timer {
  std::chrono::time_point<std::chrono::high_resolution_clock> start{
      std::chrono::high_resolution_clock::now()};
  ~Timer() {
    std::chrono::duration<float, std::milli> elapsed =
        std::chrono::high_resolution_clock::now() - start;
    if (elapsed.count() < 1000.0 / 240) {
      std::this_thread::sleep_for(
          std::chrono::duration<float, std::milli>(1000.0 / 240) - elapsed);
    }
  }
};

namespace AdrianEngine {
Application *Application::ms_instance = nullptr;
Application::Application() {
  AE_CORE_ASSERT(!ms_instance, "Application already exists!")
  ms_instance = this;
  m_window = std::unique_ptr<Window>{Window::create()};
  m_window->setEventCallback(std::bind_front(&Application::onEvent, this));
  m_imGuiLayer = new ImGuiLayer;
  pushOverlay(m_imGuiLayer);
}

void Application::run() {
  while (m_isRunning) {
    m_timestep.onUpdate();
    for (auto *layer : m_layerStack) {
      layer->onUpdate(m_timestep);
    }

    m_imGuiLayer->begin();
    for (auto *layer : m_layerStack) {
      layer->onImGuiRender();
    }
    m_imGuiLayer->end();

    m_window->onUpdate();
  }
}

void Application::onEvent(Event &e) {
  EventDispatcher dispatcher{e};
  dispatcher.dispatch<WindowCloseEvent>([this](const WindowCloseEvent &) {
    m_isRunning = false;
    return true;
  });
  for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
    (*--it)->onEvent(e);
    if (e.isHandled()) break;
  }
}

void Application::pushLayer(Layer *layer) {
  m_layerStack.pushLayer(layer);
  layer->onAttach();
}

void Application::pushOverlay(Layer *layer) {
  m_layerStack.pushOverlay(layer);
  layer->onAttach();
}
}  // namespace AdrianEngine