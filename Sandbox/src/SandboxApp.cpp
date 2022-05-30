#include "AdrianEngine.h"
#include "AdrianEngine/Log.h"
#include "imgui.h"
class ExampleLayer : public AdrianEngine::Layer {
public:
  ExampleLayer() : Layer("example") {}
  void onUpdate() override {
    if (AdrianEngine::Input::isKeyPressed(AE_KEY_TAB)) {
      AE_TRACE("Tab key is pressed");
    }
  }

  void onEvent(AdrianEngine::Event &event) override {
    if (event.getEventType() == AdrianEngine::EventType::KeyPressed) {
      if (const AdrianEngine::KeyPressedEvent &
              e{dynamic_cast<AdrianEngine::KeyPressedEvent &>(event)};
          e.getKeyCode() == AE_KEY_TAB)
        AE_TRACE("Tab key is pressed");
      ;
    }
  }
  void onAttach() override {}
  void onDetach() override {}
  void onImGuiRender() override {
    ImGui::Begin("Test");
    ImGui::Text("Hello");
    ImGui::End();
  }
};
class SandboxApp : public AdrianEngine::Application {
public:
  SandboxApp(/* args */) { pushLayer(new ExampleLayer); }
};

AdrianEngine::Application *AdrianEngine::createApplication() {
  return new SandboxApp{};
}
