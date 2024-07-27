#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

Renderer::Renderer(const std::string& vertexShaderPath, const std::string& fragmentShaderPath){
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	m_shader = new Shader(vertexShaderPath, fragmentShaderPath);
}

void Renderer::processFrame() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0);

	m_shader->useProgram();

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::setClearColor(float r, float g, float b) {
	clearColor = glm::vec3(r, g, b);
}