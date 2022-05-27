#pragma once
#include "Application.h"
#include "Log.h"

#ifdef AE_PLATFORM_WINDOWS

extern AdrianEngine::Application* AdrianEngine::createApplication();

int main(int argc, char** argv)
{
    AdrianEngine::Log::init();
    AE_CORE_WARN("Intialized Core Log!");
    int a = 5;
    AE_INFO("Hello from Client {0}!", a);
    auto app = AdrianEngine::createApplication();
    app->run();
    delete app;
}

#endif // AE_PLATFORM_WINDOWS