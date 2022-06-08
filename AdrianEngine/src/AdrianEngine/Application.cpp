#include "Application.h"

#include <glad/glad.h>

#include <memory>

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Events/ApplicationEvent.h"
#include "AdrianEngine/Events/Event.h"
#include "AdrianEngine/ImGui/ImGuiLayer.h"
#include "AdrianEngine/Log.h"
#include "AdrianEngine/Renderer/Buffer.h"
#include "AdrianEngine/Renderer/Shader.h"
#include "AdrianEngine/Window.h"
#include "Input.h"
#include "aepch.h"

namespace AdrianEngine {
Application *Application::ms_instance = nullptr;
Application::Application(/* args */) {
  AE_CORE_ASSERT(!ms_instance, "Application already exists!")
  ms_instance = this;
  m_window = std::unique_ptr<Window>{Window::create()};
  m_window->setEventCallback(std::bind_front(&Application::onEvent, this));
  m_imGuiLayer = new ImGuiLayer;
  pushOverlay(m_imGuiLayer);

  float vertices[3 * 7]{
      -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,  // 0
      0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,  // 1
      0.0f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f   // 2
  };
  unsigned indices[3]{0, 1, 2};

  glGenVertexArrays(1, &m_vertexArray);
  glBindVertexArray(m_vertexArray);

  m_vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
  BufferLayout layout{{ShaderDataType::Float3, "a_Position"},
                      {ShaderDataType::Float4, "a_Color"}};
  m_vertexBuffer->setLayout(layout);

  int index = 0;
  uint32_t stride = m_vertexBuffer->getLayout().stride();
  for (const auto &elem : m_vertexBuffer->getLayout()) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, elem.count(), elem.toOpenGL(),
                          elem.normalized ? GL_TRUE : GL_FALSE, stride,
                          (const void *)elem.offset);
    ++index;
  }

  m_indexBuffer.reset(IndexBuffer::create(indices, 3));

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