#pragma once

#include "Event.h"
#include "aepch.h"

namespace AdrianEngine {
class AE_API MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y)
        : m_mouseX(x)
        , m_mouseY(y)
    {
    }

    inline float getX() const { return m_mouseX; }
    inline float getY() const { return m_mouseY; }

    std::string toString() const override { return std::format("MouseMovedEvent: ({0}, {1})", getX(), getY()); }

    EVENT_CLASS_TYPE(EventType::MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

private:
    float m_mouseX;
    float m_mouseY;
};

class AE_API MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float xOffset, float yOffset)
        : m_xOffset(xOffset)
        , m_yOffset(yOffset)
    {
    }
    inline float getXOffset() const { return m_xOffset; }
    inline float getYOffset() const { return m_yOffset; }
    std::string toString() const override { return std::format("MouseScrolledEvent: ({0}, {1})", getXOffset(), getYOffset()); }

    EVENT_CLASS_TYPE(EventType::MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

private:
    float m_xOffset;
    float m_yOffset;
};

class AE_API MouseButtonEvent : public Event {
public:
    inline int getMouseButton() const { return m_button; }
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouseButton | EventCategory::EventCategoryInput)
protected:
    explicit MouseButtonEvent(int button)
        : m_button(button)
    {
    }

private:
    int m_button;
};

class AE_API MouseButtonPressedEvent : public MouseButtonEvent {

public:
    explicit MouseButtonPressedEvent(int button)
        : MouseButtonEvent(button)
    {
    }
    std::string toString() const override { return std::format("MouseButtonPressedEvent: {0}", getMouseButton()); }
    EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
};

class AE_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonReleasedEvent(int button)
        : MouseButtonEvent(button)
    {
    }
    std::string toString() const override { return std::format("MouseButtonReleasedEvent: {0}", getMouseButton()); }
    EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
};
} // namespace AdrianEngine
