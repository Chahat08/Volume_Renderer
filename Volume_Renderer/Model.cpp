#include "Model.h"
#include <vector>

Model::Model(const std::string& dataPath) :m_dataPath(dataPath){
	vertexDataSetup();

	deltaTime = 1.0f;
	m_modelMatrix = glm::mat4(1.0f);
	m_rotateSpeed = 0.0005f;
}

void Model::vertexDataSetup() {
	std::vector<GLfloat> vertexVals = { 0.0, 0.8,0.0,	1.0,0.0,0.0,
										0.7,-0.2,0.0,	0.0,1.0,0.0,
									   -0.7,-0.2,0.0,	0.0,0.0,1.0, };

	for (int i = 0; i < vertexVals.size(); ++i)
		m_vertexData[i] = vertexVals[i];

	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexData), m_vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
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

GLuint Model::getVertexArray() {
	return m_vao;
}