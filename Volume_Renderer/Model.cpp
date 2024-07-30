#include "Model.h"
#include <iostream>

Model::Model() :deltaTime(1.0f), m_modelMatrix(glm::mat4(1.0f)), m_rotateSpeed(1.0f) {}
Model::Model(const std::string& dataPath) :deltaTime(1.0f), m_modelMatrix(glm::mat4(1.0f)), m_dataPath(dataPath), m_rotateSpeed(5.0f) {
	std::cout << "here";
}

void Model::rotate(const glm::vec3& axis, float angle) {
	m_modelMatrix = glm::rotate(m_modelMatrix, angle * 1.0f * 1.0f, axis);
	std::cout << "here" << std::endl;
}

void Model::scaleUniform(float factor) {
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(factor * deltaTime));
}

glm::mat4 Model::getModelMatrix() {
	return m_modelMatrix;
}
