#pragma once
#include "Application.h"

#ifdef AE_PLATFORM_WINDOWS

extern AdrianEngine::Application* AdrianEngine::createApplication();

int main(int argc, char** argv)
{
    auto app = AdrianEngine::createApplication();
    app->run();
    delete app;
}

#endif // AE_PLATFORM_WINDOWS