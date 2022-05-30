#pragma once
#include "Application.h"
#include "aepch.h"

#ifdef AE_PLATFORM_WINDOWS

extern AdrianEngine::Application *AdrianEngine::createApplication();

int main(int argc, char **argv) {
  AdrianEngine::Log::init();
  AE_CORE_WARN("Intialized Core Log!");
  int a = 5;
  AE_INFO("Hello from Client {0}!", a);
  std::unique_ptr<AdrianEngine::Application> app{
      AdrianEngine::createApplication()};
  app->run();
}

#endif // AE_PLATFORM_WINDOWS