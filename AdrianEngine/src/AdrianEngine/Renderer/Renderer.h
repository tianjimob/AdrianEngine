#pragma once

#include <memory>

#include "AdrianEngine/Core.h"
#include "AdrianEngine/Renderer/Camera.h"
#include "AdrianEngine/Renderer/Shader.h"
#include "AdrianEngine/Renderer/VertexArray.h"
#include "glm/fwd.hpp"

namespace AdrianEngine {

class AE_API Renderer {
 public:
  static void beginScene(const OrthographicCamera &camera);
  static void endScene();
  static void submit(const std::shared_ptr<Shader> &shader,
                     const std::shared_ptr<VertexArray> &vertexArray);

 private:
  struct SceneData {
    glm::mat4 viewProjection;
  };
  static SceneData *ms_sceneData;
};

}  // namespace AdrianEngine