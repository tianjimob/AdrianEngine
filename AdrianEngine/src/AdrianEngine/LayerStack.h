#pragma once

#include "Core.h"
#include "Layer.h"
#include "aepch.h"

namespace AdrianEngine {
class AE_API LayerStack {
public:
  LayerStack();
  ~LayerStack();

  void pushLayer(Layer *layer);
  void pushOverlay(Layer *layer);
  void popLayer(Layer *layer);
  void popOverlay(Layer *layer);

  auto begin() { return m_layers.begin(); }
  auto end() { return m_layers.end(); }

private:
  std::vector<Layer *> m_layers;
  std::vector<Layer *>::iterator m_layerInsert;
};

} // namespace AdrianEngine