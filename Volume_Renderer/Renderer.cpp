#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

Renderer::Renderer(Shader* shader, Camera* camera, Model* model){
	vertexDataSetup();

	m_shader = shader;
	m_camera = camera;
	m_model = model;

	m_projection = glm::perspective(glm::radians(45.0f), (float)m_width / m_height, 0.1f, 100.0f);
}

void Renderer::vertexDataSetup() {
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

void Renderer::processFrame() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0);

	m_shader->useProgram();
	m_shader->setUniform("projection", m_projection);
	m_shader->setUniform("view", m_camera->getLookAt());
	m_shader->setUniform("model", m_model->getModelMatrix());

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::setClearColor(float r, float g, float b) {
	clearColor = glm::vec3(r, g, b);
}