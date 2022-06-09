#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "aepch.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/matrix.hpp"

namespace AdrianEngine {
OrthographicCamera::OrthographicCamera(float left, float right, float bottom,
                                       float top)
    : m_projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)) {
  recaculate();
}

inline const glm::mat4& OrthographicCamera::getProjection() const {
  return m_projection;
}

inline const glm::mat4& OrthographicCamera::getView() const { return m_view; }

inline const glm::mat4& OrthographicCamera::getViewProjection() const {
  return m_viewProjection;
}

inline const glm::vec3& OrthographicCamera::getPosition() const {
  return m_position;
}

inline void OrthographicCamera::setPosition(const glm::vec3& position) {
  m_position = position;
  recaculate();
}

inline float OrthographicCamera::getRotation() const { return m_rotation; }

inline void OrthographicCamera::setRotation(float rotation) {
  m_rotation = rotation;
  recaculate();
}

inline void OrthographicCamera::recaculate() {
  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), m_position) *
      glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));

  m_view = glm::inverse(transform);
  m_viewProjection = m_projection * m_view;
}
}  // namespace AdrianEngine