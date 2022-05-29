#include "AdrianEngine.h"
#include "AdrianEngine/Log.h"
class ExampleLayer : public AdrianEngine::Layer {
public:
  ExampleLayer() : Layer("example") {}
  void onUpdate() override { AE_INFO("ExampleLayer::Update"); }
  void onEvent(AdrianEngine::Event &event) override {
    AE_TRACE("{0}", event.toString());
  }
  void onAttach() override {}
  void onDetach() override {}
};
class SandboxApp : public AdrianEngine::Application {
public:
  SandboxApp(/* args */) {
    pushLayer(new ExampleLayer);
    pushLayer(new AdrianEngine::ImGuiLayer);
  }
  ~SandboxApp() {}
};

AdrianEngine::Application *AdrianEngine::createApplication() {
  return new SandboxApp{};
}
