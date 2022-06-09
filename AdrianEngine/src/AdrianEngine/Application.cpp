#include "Application.h"

#include <glad/glad.h>
#include <stdint.h>

#include <memory>

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Events/ApplicationEvent.h"
#include "AdrianEngine/Events/Event.h"
#include "AdrianEngine/ImGui/ImGuiLayer.h"
#include "AdrianEngine/Log.h"
#include "AdrianEngine/Renderer/Buffer.h"
#include "AdrianEngine/Renderer/Shader.h"
#include "AdrianEngine/Renderer/VertexArray.h"
#include "AdrianEngine/Window.h"
#include "Input.h"
#include "aepch.h"

namespace AdrianEngine {
Application *Application::ms_instance = nullptr;
Application::Application() {
  AE_CORE_ASSERT(!ms_instance, "Application already exists!")
  ms_instance = this;
  m_window = std::unique_ptr<Window>{Window::create()};
  m_window->setEventCallback(std::bind_front(&Application::onEvent, this));
  m_imGuiLayer = new ImGuiLayer;
  pushOverlay(m_imGuiLayer);

  std::array vertices{
      -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,  // 0
      0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,  // 1
      0.0f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f   // 2
  };
  std::array<uint32_t, 3> indices{0, 1, 2};

  std::shared_ptr<VertexBuffer> vertexBuffer;
  m_vertexArray.reset(VertexArray::create());
  vertexBuffer.reset(VertexBuffer::create(vertices.data(), sizeof(vertices)));
  BufferLayout layout{{ShaderDataType::Float3, "a_Position"},
                      {ShaderDataType::Float4, "a_Color"}};
  vertexBuffer->setLayout(layout);
  m_vertexArray->addVertexBuffer(vertexBuffer);
  std::shared_ptr<IndexBuffer> indexBuffer;
  indexBuffer.reset(IndexBuffer::create(indices.data(), 3));
  m_vertexArray->setIndexBuffer(indexBuffer);

  std::string_view vertexShader = R"(
    #version 330 core

    layout (location = 0) in vec3 a_Position;
    layout (location = 1) in vec4 a_Color;

    out vec3 v_Position;
    out vec4 v_Color;

    void main() {
      v_Position = a_Position;
      v_Color = a_Color;
      gl_Position = vec4(a_Position, 1.0f);
    }
  )";

  std::string_view fragmentShader = R"(
    #version 330 core

    out vec4 color;
    in vec3 v_Position;
    in vec4 v_Color;

    void main() {
      color = v_Color;
    }
  )";
  m_shader = std::make_unique<Shader>(vertexShader, fragmentShader);
}

void Application::run() {
  while (m_isRunning) {
    glClearColor(.1f, .1f, .1f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    m_shader->bind();
    m_vertexArray->bind();
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