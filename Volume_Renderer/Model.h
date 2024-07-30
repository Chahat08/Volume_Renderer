#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class Model {
public:
	Model(const std::string& dataPath);

	void rotate(const glm::vec3& axis, float angle);
	void scaleUniform(float factor);

	float deltaTime;

	glm::mat4 getModelMatrix();
	GLuint getVertexArray();
private:
	float m_rotateSpeed;

	glm::mat4 m_modelMatrix;
	std::string m_dataPath;

	GLfloat m_vertexData[18];
	GLuint m_vbo, m_vao;

	void readTextures();
	void vertexDataSetup();
};