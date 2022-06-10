#include <stdint.h>

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
#include "AdrianEngine/Renderer/Renderer.h"
#include "AdrianEngine/Renderer/Shader.h"
#include "AdrianEngine/Renderer/VertexArray.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"

class ExampleLayer : public AdrianEngine::Layer {
 public:
  ExampleLayer() : Layer("example") {}
  void onUpdate(const AdrianEngine::Timestep &ts) override {
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

    if (AdrianEngine::Input::isKeyPressed(AE_KEY_D)) {
      m_trianglePosition.x += m_cameraSpeed * ts;
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_A)) {
      m_trianglePosition.x -= m_cameraSpeed * ts;
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_W)) {
      m_trianglePosition.y += m_cameraSpeed * ts;
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_S)) {
      m_trianglePosition.y -= m_cameraSpeed * ts;
    }

    if (AdrianEngine::Input::isKeyPressed(AE_KEY_L)) {
      m_squarePosition.x += m_cameraSpeed * ts;
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_J)) {
      m_squarePosition.x -= m_cameraSpeed * ts;
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_I)) {
      m_squarePosition.y += m_cameraSpeed * ts;
    }
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_K)) {
      m_squarePosition.y -= m_cameraSpeed * ts;
    }

    m_orthoCamera.setPosition(m_cameraPosition);
    m_orthoCamera.setRotation(m_rotation);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    AdrianEngine::RendererCommand::setClearColor({.1f, .1f, .0f, 1.0f});
    AdrianEngine::RendererCommand::clear();

    AdrianEngine::Renderer::beginScene(m_orthoCamera);
    for (int i = 0; i < 20; ++i) {
      for (int j = 0; j < 20; ++j) {
        glm::vec3 position{i * 0.1f, j * 0.1f, 0.0f};
        AdrianEngine::Renderer::submit(
            m_shader, m_squareVA,
            glm::translate(glm::mat4(1.0f), m_squarePosition + position) *
                scale);
        AdrianEngine::Renderer::submit(
            m_shader, m_vertexArray,
            glm::translate(glm::mat4(1.0f), m_trianglePosition + position) *
                scale);
      }
    }

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

    std::array squareVertices{
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,  // 0
        0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,  // 1
        0.5f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f,  // 2
        -0.5f, 0.5f,  0.0f, 0.2f, 0.3f, 0.8f, 1.0f   // 3
    };
    std::array<uint32_t, 6> squareIndices{0, 1, 2, 2, 3, 0};

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

    std::shared_ptr<VertexBuffer> squareVB;
    m_squareVA.reset(VertexArray::create());
    squareVB.reset(
        VertexBuffer::create(squareVertices.data(), sizeof(squareVertices)));
    BufferLayout squareLayout{{ShaderDataType::Float3, "a_Position"},
                              {ShaderDataType::Float4, "a_Color"}};
    squareVB->setLayout(squareLayout);
    m_squareVA->addVertexBuffer(squareVB);
    std::shared_ptr<IndexBuffer> squareIB;
    squareIB.reset(IndexBuffer::create(squareIndices.data(), 6));
    m_squareVA->setIndexBuffer(squareIB);

    std::string_view vertexShader = R"(
    #version 330 core

    layout (location = 0) in vec3 a_Position;
    layout (location = 1) in vec4 a_Color;

    out vec3 v_Position;
    out vec4 v_Color;

    uniform mat4 u_ViewProjection;
    uniform mat4 u_Model;

    void main() {
      v_Position = a_Position;
      v_Color = a_Color;
      gl_Position = u_ViewProjection * u_Model *vec4(a_Position, 1.0f);
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
  std::shared_ptr<AdrianEngine::VertexArray> m_squareVA;
  AdrianEngine::OrthographicCamera m_orthoCamera{-1.6f, 1.6f, -0.9f, 0.9f};
  float m_cameraSpeed{1.5f};
  float m_rotation{0.0};
  glm::vec3 m_cameraPosition{0.0f, 0.0f, 0.0f};
  glm::vec3 m_trianglePosition{0.0f, 0.0f, 0.0f};
  glm::vec3 m_squarePosition{0.0f, 0.0f, 0.0f};
};
class SandboxApp : public AdrianEngine::Application {
 public:
  SandboxApp() { pushLayer(new ExampleLayer); }
};

AdrianEngine::Application *AdrianEngine::createApplication() {
  return new SandboxApp{};
}
