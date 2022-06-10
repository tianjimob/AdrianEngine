#include "Layer.h"

namespace AdrianEngine {
Layer::Layer(std::string_view name) : m_debugName(name) {}

std::string_view Layer::getName() const { return m_debugName; }

}  // namespace AdrianEngine