#include "LayerStack.h"

namespace AdrianEngine {
LayerStack::LayerStack() {}

LayerStack::~LayerStack() {
  for (auto *layer : m_layers) {
    delete layer;
  }
}

void LayerStack::pushLayer(Layer *layer) {
  m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
  ++m_layerInsertIndex;
}

void LayerStack::pushOverlay(Layer *layer) { m_layers.emplace_back(layer); }

void LayerStack::popLayer(Layer *layer) {
  auto it = std::find(m_layers.begin(), m_layers.end(), layer);
  if (it != m_layers.end()) {
    m_layers.erase(it);
    --m_layerInsertIndex;
  }
}

void LayerStack::popOverlay(Layer *layer) {
  auto it = std::find(m_layers.begin(), m_layers.end(), layer);
  if (it != m_layers.end()) {
    m_layers.erase(it);
  }
}
} // namespace AdrianEngine