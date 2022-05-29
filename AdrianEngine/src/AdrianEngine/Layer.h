#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "aepch.h"

namespace AdrianEngine {
class AE_API Layer {
public:
  explicit Layer(std::string_view name = "Layer");
  virtual ~Layer();
  virtual void onAttach() = 0;
  virtual void onDetach() = 0;
  virtual void onUpdate() = 0;
  virtual void onEvent(Event &event) = 0;

  inline std::string_view getName() const { return m_debugName; }

private:
  std::string m_debugName;
};
} // namespace AdrianEngine
