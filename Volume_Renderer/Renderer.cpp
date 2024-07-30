#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <vector>

Renderer::Renderer(Shader* shader, Camera* camera, Model* model){
	m_shader = shader;
	m_camera = camera;
	m_model = model;

	m_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	setClearColor(0.11, 0.004, 0.106);
}

void Renderer::processFrame() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0);

	m_shader->useProgram();
	m_shader->setUniform("projection", m_projection);
	m_shader->setUniform("view", m_camera->getLookAt());
	m_shader->setUniform("model", m_model->getModelMatrix());

	glBindVertexArray(m_model->getVertexArray());
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::setClearColor(float r, float g, float b) {
	clearColor = glm::vec3(r, g, b);
}