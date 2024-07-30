#include "Camera.h"

Camera::Camera() {
	setDefaults();
	updateVectors();
}

Camera::Camera(glm::vec3 position) {
	setDefaults(position);
	updateVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 target) {
	setDefaults(position, target);
	updateVectors();
}

void Camera::setDefaults(glm::vec3 position, glm::vec3 target) {
	m_position = position;
	m_target = target;
	m_worldUp = glm::vec3(0.0, 1.0, 0.0);

	deltaTime = 1.0f;
	m_translate_speed = 0.01f;
	m_lookaround_angle_mag_degrees = 0.1f;
}

void Camera::updateVectors() {
	glm::vec3 direction = getCameraDirection();
	m_right = glm::normalize(glm::cross(getCameraDirection(), m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, getCameraDirection()));

	m_lookAt = getLookAt();
}

glm::vec3 Camera::getCameraDirection() {
	return glm::normalize(m_target - m_position);
}

glm::mat4 Camera::getLookAt() {
	return glm::lookAt(m_position, m_position + m_target, m_up);
}	

void Camera::setPosition(const glm::vec3& position) {
	m_position = position;
	updateVectors();
}

glm::vec3 Camera::getPosition() {
	return m_position;
}

void Camera::setTarget(const glm::vec3& target) {
	m_target = target;
	updateVectors();
}

glm::vec3 Camera::getTarget() {
	return m_target;
}

void Camera::move(Movement m) {

	switch (m) {
	case MOVE_FORWARD:
		m_position += m_translate_speed * getCameraDirection() * deltaTime;
		break;
	case MOVE_BACKWARD:
		m_position -= m_translate_speed * getCameraDirection() * deltaTime;
		break;
	case MOVE_RIGHT:
		m_position += m_translate_speed * m_right * deltaTime;
		break;
	case MOVE_LEFT:
		m_position -= m_translate_speed * m_right * deltaTime;
		break;
	case MOVE_UPWARD:
		m_position += m_translate_speed * m_up * deltaTime;
		break;
	case MOVE_DOWNWARD:
		m_position -= m_translate_speed * m_up * deltaTime;
		break;
	case LOOK_UP:
		break;
	case LOOK_DOWN:
		break;
	case LOOK_LEFT:
		break;
	case LOOK_RIGHT:
		break; 
	}

	updateVectors();
	
}