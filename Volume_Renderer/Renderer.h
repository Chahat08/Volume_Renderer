#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class Renderer {
public:
	Renderer(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	
	void processFrame();

	void setClearColor(float r, float g, float b);
private:
	glm::vec3 clearColor;
	
	Shader* m_shader;

	GLfloat m_vertexData[18];
	GLuint m_vbo, m_vao;
};