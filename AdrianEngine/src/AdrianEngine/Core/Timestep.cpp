#include "Timestep.h"

#include "aepch.h"

namespace AdrianEngine {
inline void Timestep::onUpdate() {
  timepoint now = clock::now();
  m_delta = now - m_lastFrameTime;
  m_lastFrameTime = now;
}

inline Timestep::operator float() const { return getSeconds(); }

inline float Timestep::getMilli() const { return m_delta.count() * 1000; }

inline float Timestep::getSeconds() const { return m_delta.count(); }

}  // namespace AdrianEngine