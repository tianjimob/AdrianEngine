#include <memory>

#include "AdrianEngine.h"
#include "AdrianEngine/Events/Event.h"
#include "AdrianEngine/Events/KeyEvent.h"
#include "AdrianEngine/Events/MouseEvent.h"
#include "AdrianEngine/Input.h"
#include "AdrianEngine/KeyCodes.h"
#include "AdrianEngine/Renderer/Buffer.h"
#include "AdrianEngine/Renderer/Shader.h"
#include "AdrianEngine/Renderer/VertexArray.h"
#include "glm/fwd.hpp"
#include "imgui.h"

class ExampleLayer : public AdrianEngine::Layer {
 public:
  ExampleLayer() : Layer("example") {}
  void onUpdate() override {
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_TAB)) {
      AE_TRACE("Tab key is pressed");
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_RIGHT)) {
      orthoCamera.setPosition(orthoCamera.getPosition() +
                              glm::vec3(-0.01f, 0.0f, 0.0f));
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_LEFT)) {
      orthoCamera.setPosition(orthoCamera.getPosition() +
                              glm::vec3(0.01f, 0.0f, 0.0f));
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_UP)) {
      orthoCamera.setPosition(orthoCamera.getPosition() +
                              glm::vec3(0.0f, -0.01f, 0.0f));
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_DOWN)) {
      orthoCamera.setPosition(orthoCamera.getPosition() +
                              glm::vec3(0.01f, 0.01f, 0.0f));
    }
    AdrianEngine::RendererCommand::setClearColor({.1f, .1f, .0f, 1.0f});
    AdrianEngine::RendererCommand::clear();

    AdrianEngine::Renderer::beginScene();

    m_shader->bind();
    m_shader->setUniform("u_ViewProjection", orthoCamera.getViewProjection());
    AdrianEngine::Renderer::submit(m_vertexArray);

    AdrianEngine::Renderer::endScene();
  }

  void onEvent(AdrianEngine::Event &event) override {
    AdrianEngine::EventDispatcher dispatcher{event};
    dispatcher.dispatch<AdrianEngine::KeyPressedEvent>(
        [](const AdrianEngine::KeyPressedEvent &e) {
          if (e.getKeyCode() == AE_KEY_TAB) AE_TRACE("Tab key is pressed");
          return true;
        });
  }
  void onAttach() override {
    using namespace AdrianEngine;
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

    uniform mat4 u_ViewProjection;

    void main() {
      v_Position = a_Position;
      v_Color = a_Color;
      gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
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
  void onDetach() override {}
  void onImGuiRender() override {
    ImGui::Begin("Test");
    ImGui::Text("Hello");
    ImGui::End();
  }

 private:
  std::shared_ptr<AdrianEngine::Shader> m_shader;
  std::shared_ptr<AdrianEngine::VertexArray> m_vertexArray;
  AdrianEngine::OrthographicCamera orthoCamera{-1.0f, 1.0f, -1.0f, 1.0f};
};
class SandboxApp : public AdrianEngine::Application {
 public:
  SandboxApp(/* args */) { pushLayer(new ExampleLayer); }
};

AdrianEngine::Application *AdrianEngine::createApplication() {
  return new SandboxApp{};
}
