#pragma once
#include <string>
#include <glad/glad.h>

class Shader {
public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	void useProgram();
private:
	GLuint m_vertexShader, m_fragmentShader;
	GLuint m_program;
};