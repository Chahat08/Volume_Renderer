#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <vector>

Renderer::Renderer(Shader* shader, Camera* camera, Model* model){
	m_shader = shader;
	m_camera = camera;
	m_model = model;
	
	//m_projection = glm::perspective(glm::radians(45.0f), (float)m_width / m_height, 0.1f, 100.0f);
	m_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -2.0f, 2.0f);
	setClearColor(1.0,1.0,1.0);
}

void Renderer::processFrame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0);

	m_shader->useProgram();
	m_shader->setUniform("projection", m_projection);
	m_shader->setUniform("view", m_camera->getLookAt());
	m_shader->setUniform("model", m_model->getModelMatrix());

	glBindVertexArray(m_model->getVertexArray());
	for (int i = 0; i < m_model->getNumTriangles() / 2; ++i) {
		glBindTexture(GL_TEXTURE_2D, m_model->getTextureIds()[i]);
		glDrawArrays(GL_TRIANGLES, i * 8, 6);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void Renderer::setClearColor(float r, float g, float b) {
	clearColor = glm::vec3(r, g, b);
}