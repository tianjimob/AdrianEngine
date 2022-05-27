#include "AdrianEngine.h"

class SandboxApp : public AdrianEngine::Application {
public:
    SandboxApp(/* args */) { }
    ~SandboxApp() { }
};

AdrianEngine::Application* AdrianEngine::createApplication()
{
    return new SandboxApp {};
}
