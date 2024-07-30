#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class Model {
public:
	Model();
	Model(const std::string& dataPath);

	void rotate(const glm::vec3& axis, float angle);
	void scaleUniform(float factor);

	float deltaTime;

	glm::mat4 getModelMatrix();
private:
	float m_rotateSpeed;

	glm::mat4 m_modelMatrix;
	std::string m_dataPath;

};