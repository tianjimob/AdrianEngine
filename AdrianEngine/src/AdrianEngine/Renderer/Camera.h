#include <glm/glm.hpp>

#include "AdrianEngine/Core.h"

namespace AdrianEngine {
class AE_API OrthographicCamera {
 public:
  OrthographicCamera(float left, float right, float bottom, float top);

  const glm::mat4 &getProjection() const;
  const glm::mat4 &getView() const;
  const glm::mat4 &getViewProjection() const;

  const glm::vec3 &getPosition() const;
  void setPosition(const glm::vec3 &position);

  float getRotation() const;
  void setRotation(float rotation);

 private:
  void recaculate();

 private:
  glm::mat4 m_projection;
  glm::mat4 m_view{1.0f};
  glm::mat4 m_viewProjection;
  glm::vec3 m_position{0.0f, 0.0f, 0.0f};
  float m_rotation{0.0f};
};
}  // namespace AdrianEngine