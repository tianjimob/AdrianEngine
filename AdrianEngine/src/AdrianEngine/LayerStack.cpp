#include "LayerStack.h"

namespace AdrianEngine {
LayerStack::LayerStack() { m_layerInsert = m_layers.begin(); }

LayerStack::~LayerStack() {
  for (auto *layer : m_layers) {
    delete layer;
  }
}

void LayerStack::pushLayer(Layer *layer) {
  m_layerInsert = m_layers.emplace(m_layerInsert, layer);
}

void LayerStack::pushOverlay(Layer *layer) { m_layers.emplace_back(layer); }

void LayerStack::popLayer(Layer *layer) {
  auto it = std::find(m_layers.begin(), m_layers.end(), layer);
  if (it != m_layers.end()) {
    m_layers.erase(it);
    --m_layerInsert;
  }
}

void LayerStack::popOverlay(Layer *layer) {
  auto it = std::find(m_layers.begin(), m_layers.end(), layer);
  if (it != m_layers.end()) {
    m_layers.erase(it);
  }
}
} // namespace AdrianEngine