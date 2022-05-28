#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "aepch.h"

namespace AdrianEngine {
class AE_API Application {
public:
    Application();
    virtual ~Application();
    void run();

    void onEvent(Event& e);
private:
    std::unique_ptr<Window> m_window;
    bool m_isRunning = true;
};

// to be defined in CLIENT
Application* createApplication();

} // namespace AdrianEngine
