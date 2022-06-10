#pragma once

#include "AdrianEngine/Core/Timestep.h"
#include "Core.h"
#include "Events/Event.h"
#include "aepch.h"

namespace AdrianEngine {
class AE_API Layer {
 public:
  explicit Layer(std::string_view name = "Layer");
  virtual ~Layer() = default;
  virtual void onAttach() = 0;
  virtual void onDetach() = 0;
  virtual void onUpdate(const Timestep& ts) = 0;
  virtual void onEvent(Event& event) = 0;
  virtual void onImGuiRender() = 0;

  std::string_view getName() const;

 private:
  std::string m_debugName;
};
}  // namespace AdrianEngine
