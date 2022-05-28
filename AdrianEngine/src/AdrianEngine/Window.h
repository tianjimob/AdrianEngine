#pragma once

#include "aepch.h"

#include "Core.h"
#include "Events/Event.h"

namespace AdrianEngine {
struct WindowProps {
    std::string title;
    unsigned width;
    unsigned height;

    WindowProps(std::string_view title = "Adrian Engine", unsigned width = 1280, unsigned height = 720)
        : title { title }
        , width { width }
        , height { height }
    {
    }
};

class AE_API Window {
public:
    using EventCallback = std::function<void(Event&)>;
    virtual ~Window() = default;
    virtual void onUpdate() = 0;
    virtual unsigned getWidth() const = 0;
    virtual unsigned getHeight() const = 0;

    // Window attributes
    virtual void setEventCallback(const EventCallback& callback) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual bool isVSync() const = 0;

    static Window* create(const WindowProps& props = WindowProps {});
};
} // namespace AdrianEngine
