#pragma once

#include "Event.h"
#include "aepch.h"

namespace AdrianEngine {
class AE_API KeyEvent : public Event {
public:
  inline int getKeyCode() const { return m_keyCode; }

protected:
  explicit KeyEvent(int keyCode) : m_keyCode(keyCode) {}

  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard |
                       EventCategory::EventCategoryInput)

private:
  int m_keyCode;
};

class AE_API KeyPressedEvent : public KeyEvent {
public:
  KeyPressedEvent(int keyCode, int repeatCount)
      : KeyEvent(keyCode), m_repeatCount(repeatCount) {}
  inline int getRepeatCount() const { return m_repeatCount; }
  std::string toString() const override {
    return std::format("KeyPressedEvent: {0} ({1} repeats)", getKeyCode(),
                       m_repeatCount);
  }

  EVENT_CLASS_TYPE(EventType::KeyPressed)
private:
  int m_repeatCount;
};

class AE_API KeyReleasedEvent : public KeyEvent {
public:
  explicit KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}
  std::string toString() const override {
    return std::format("KeyReleasedEvent: {0}", getKeyCode());
  }

  EVENT_CLASS_TYPE(EventType::KeyReleased)
};

class AE_API KeyTypedEvent : public KeyEvent {
public:
  explicit KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}
  std::string toString() const override {
    return std::format("KeyTypedEvent: {0}", getKeyCode());
  }

  EVENT_CLASS_TYPE(EventType::KeyTyped)
};
} // namespace AdrianEngine
