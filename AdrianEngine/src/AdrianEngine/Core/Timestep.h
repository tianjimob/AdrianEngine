#pragma once

#include <chrono>
#include <ratio>

#include "AdrianEngine/Core.h"

namespace AdrianEngine {
class AE_API Timestep {
 public:
  void onUpdate();
  operator float() const;  // return delta time in seconds
  float getMilli() const;
  float getSeconds() const;

 private:
  using clock = std::chrono::high_resolution_clock;
  using timepoint = std::chrono::time_point<clock>;
  using duration = std::chrono::duration<float, std::ratio<1, 1>>;
  timepoint m_lastFrameTime{clock::now()};
  duration m_delta{0};
};
}  // namespace AdrianEngine