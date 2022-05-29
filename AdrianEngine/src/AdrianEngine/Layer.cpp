#include "Layer.h"

namespace AdrianEngine {
Layer::Layer(std::string_view name) : m_debugName(name) {}

Layer::~Layer() {}
} // namespace AdrianEngine