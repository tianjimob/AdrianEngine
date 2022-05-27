#pragma once
#include "Core.h"

namespace AdrianEngine {
class AE_API Application {
private:
    /* data */
public:
    Application(/* args */);
    virtual ~Application();
    void run();
};

// to be defined in CLIENT
Application* createApplication();

} // namespace AdrianEngine
