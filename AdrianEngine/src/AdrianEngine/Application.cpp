#include "Application.h"

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Events/ApplicationEvent.h"
#include "AdrianEngine/Events/Event.h"
#include "AdrianEngine/ImGui/ImGuiLayer.h"
#include "AdrianEngine/Log.h"
#include "AdrianEngine/Window.h"
#include "Input.h"
#include "aepch.h"
#include <glad/glad.h>

namespace AdrianEngine {
Application *Application::ms_instance = nullptr;
Application::Application(/* args */) {
  AE_CORE_ASSERT(!ms_instance, "Application already exists!")
  ms_instance = this;
  m_window = std::unique_ptr<Window>{Window::create()};
  m_window->setEventCallback(std::bind_front(&Application::onEvent, this));
  m_imGuiLayer = new ImGuiLayer;
  pushOverlay(m_imGuiLayer);

  glGenVertexArrays(1, &m_vertexArray);
  glBindVertexArray(m_vertexArray);

  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  float vertices[3 * 3]{-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                        0.0f,  0.0f,  0.5f, 0.0f};
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

  glGenBuffers(1, &m_indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
  unsigned indices[3]{0, 1, 2};
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
}

void Application::run() {
  while (m_isRunning) {
    glClearColor(.1f, .1f, .1f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_vertexArray);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

    for (auto *layer : m_layerStack) {
      layer->onUpdate();
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
    if (e.isHandled())
      break;
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
} // namespace AdrianEngine