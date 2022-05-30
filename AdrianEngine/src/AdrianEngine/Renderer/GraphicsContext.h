#pragma once

#include "AdrianEngine/Core.h"
namespace AdrianEngine {
class AE_API GraphicsContext {
public:
  virtual ~GraphicsContext() = default;
  virtual void init() = 0;
  virtual void swapBuffers() = 0;
};
} // namespace AdrianEngine