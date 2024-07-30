#include "Model.h"

Model::Model(const std::string& dataPath) :m_dataPath(dataPath){
	deltaTime = 1.0f;
	m_modelMatrix = glm::mat4(1.0f);
	m_rotateSpeed = 0.0005f;
}

void Model::rotate(const glm::vec3& axis, float angle) {
	m_modelMatrix = glm::rotate(m_modelMatrix, angle * deltaTime * m_rotateSpeed, axis);
}

void Model::scaleUniform(float factor) {
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(factor * deltaTime));
}

glm::mat4 Model::getModelMatrix() {
	return m_modelMatrix;
}
