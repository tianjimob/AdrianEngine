#include "AdrianEngine.h"
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
      AdrianEngine::KeyPressedEvent &e{
          dynamic_cast<AdrianEngine::KeyPressedEvent &>(event)};
      // AE_TRACE("{0}", (char)e.getKeyCode());
      if (e.getKeyCode() == AE_KEY_TAB)
        AE_TRACE("Tab key is pressed");
      ;
    }
  }
  void onAttach() override {}
  void onDetach() override {}
  void onImGuiRender() override {}
};
class SandboxApp : public AdrianEngine::Application {
public:
  SandboxApp(/* args */) { pushLayer(new ExampleLayer); }
  ~SandboxApp() {}
};

AdrianEngine::Application *AdrianEngine::createApplication() {
  return new SandboxApp{};
}
