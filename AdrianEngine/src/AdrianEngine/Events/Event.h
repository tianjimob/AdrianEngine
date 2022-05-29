#pragma once
#include "AdrianEngine/Core.h"

#include "aepch.h"

namespace AdrianEngine {

/**
 * @brief Event are currently blocking, meaning when an event occurs it
 * immediately gets dispatched and must be dealt with right then
 * an there.
 * @todo a better strategy might be to buffer events in an event bus and
 * process them during the "event" part of the update stage.
 */

enum class EventType {
  None = 0,

  WindowClose,
  WindowResize,
  WindowFocus,
  WindowMoved,

  AppTick,
  AppUpdate,
  AppRender,

  KeyPressed,
  KeyReleased,

  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
  MouseScrolled
};

enum EventCategory {
  None = 0,
  EventCategoryApplication = bitLShift(0),
  EventCategoryInput = bitLShift(1),
  EventCategoryKeyboard = bitLShift(2),
  EventCategoryMouse = bitLShift(3),
  EventCategoryMouseButton = bitLShift(4)
};

#define EVENT_CLASS_TYPE(type)                                                 \
  static EventType getStaticType() { return (type); }                          \
  virtual EventType getEventType() const override { return getStaticType(); }  \
  virtual std::string_view getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                         \
  virtual int getCategoryFlags() const override { return category; }

class AE_API Event {
  friend class EventDispatcher;

public:
  virtual ~Event() = default;
  virtual EventType getEventType() const = 0;
  virtual std::string_view getName() const = 0;
  virtual int getCategoryFlags() const = 0;
  virtual std::string toString() const { return std::string{getName()}; };

  inline bool isCategory(EventCategory category) const {
    return getCategoryFlags() & category;
  }
  inline bool isHandled() const { return m_handled; }

private:
  bool m_handled{false};
};

class EventDispatcher {
  template <typename T> using EventCallback = std::function<bool(T &)>;

public:
  explicit EventDispatcher(Event &event) : m_event(event) {}

  template <typename T> bool dispatch(EventCallback<T> callback) {
    if (m_event.getEventType() == T::getStaticType()) {
      m_event.m_handled = callback(*reinterpret_cast<T *>(&m_event));
      return true;
    }
    return false;
  }

private:
  Event &m_event;
};
} // namespace AdrianEngine
