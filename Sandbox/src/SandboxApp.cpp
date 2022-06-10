#include <format>
#include <memory>

#include "AdrianEngine.h"
#include "AdrianEngine/Core/Timestep.h"
#include "AdrianEngine/Events/Event.h"
#include "AdrianEngine/Events/KeyEvent.h"
#include "AdrianEngine/Events/MouseEvent.h"
#include "AdrianEngine/Input.h"
#include "AdrianEngine/KeyCodes.h"
#include "AdrianEngine/Log.h"
#include "AdrianEngine/Renderer/Buffer.h"
#include "AdrianEngine/Renderer/Shader.h"
#include "AdrianEngine/Renderer/VertexArray.h"
#include "glm/fwd.hpp"
#include "imgui.h"

class ExampleLayer : public AdrianEngine::Layer {
 public:
  ExampleLayer() : Layer("example") {}
  void onUpdate(const AdrianEngine::Timestep &ts) override {
    AE_INFO("Delta time: {0}s {1}ms", ts.getSeconds(), ts.getMilli());
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_RIGHT)) {
      m_cameraPosition.x += m_cameraSpeed * ts;
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_LEFT)) {
      m_cameraPosition.x -= m_cameraSpeed * ts;
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_UP)) {
      m_cameraPosition.y += m_cameraSpeed * ts;
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_DOWN)) {
      m_cameraPosition.y -= m_cameraSpeed * ts;
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_SPACE)) {
      m_rotation -= 2.0f * ts;
    }

    m_orthoCamera.setPosition(m_cameraPosition);
    m_orthoCamera.setRotation(m_rotation);
    AdrianEngine::RendererCommand::setClearColor({.1f, .1f, .0f, 1.0f});
    AdrianEngine::RendererCommand::clear();

    AdrianEngine::Renderer::beginScene(m_orthoCamera);
    AdrianEngine::Renderer::submit(m_shader, m_vertexArray);
    AdrianEngine::Renderer::endScene();
  }

  void onEvent(AdrianEngine::Event &event) override {}
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
  void onImGuiRender() override {}

 private:
  std::shared_ptr<AdrianEngine::Shader> m_shader;
  std::shared_ptr<AdrianEngine::VertexArray> m_vertexArray;
  AdrianEngine::OrthographicCamera m_orthoCamera{-1.6f, 1.6f, -0.9f, 0.9f};
  float m_cameraSpeed{1.0f};
  float m_rotation{0.0};
  glm::vec3 m_cameraPosition{0.0f, 0.0f, 0.0f};
};
class SandboxApp : public AdrianEngine::Application {
 public:
  SandboxApp() { pushLayer(new ExampleLayer); }
};

AdrianEngine::Application *AdrianEngine::createApplication() {
  return new SandboxApp{};
}
