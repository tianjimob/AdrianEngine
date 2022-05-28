#pragma once

#include "Event.h"

#include "aepch.h"

namespace AdrianEngine {
class AE_API WindowResizeEvent : public Event {
public:
  explicit WindowResizeEvent(unsigned width, unsigned height)
      : m_width(width), m_height(height) {}
  inline unsigned getWidth() const { return m_width; }
  inline unsigned getHeight() const { return m_height; }
  std::string toString() const override {
    return std::format("WindowResizeEvent: {0}, {1}", getWidth(), getHeight());
  }

  EVENT_CLASS_TYPE(EventType::WindowResize)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

private:
  unsigned m_width;
  unsigned m_height;
};

class AE_API WindowCloseEvent : public Event {
public:
  EVENT_CLASS_TYPE(EventType::WindowClose)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class AE_API AppTickEvent : public Event {
public:
  EVENT_CLASS_TYPE(EventType::AppTick)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class AE_API AppUpdateEvent : public Event {
public:
  EVENT_CLASS_TYPE(EventType::AppUpdate)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class AE_API AppRenderEvent : public Event {
public:
  EVENT_CLASS_TYPE(EventType::AppRender)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

} // namespace AdrianEngine
