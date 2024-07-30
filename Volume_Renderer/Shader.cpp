#include "Shader.h"
#include <fstream>
#include <sstream>
#include <type_traits>

std::string readFile(const std::string& filePath) {
	std::ifstream file(filePath, std::ios::in);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

Shader::Shader(const std::string& vsPath, const std::string& fsPath) {
	// VERTEX SHADER
	std::string vsSource = readFile(vsPath);
	const char* vertexShaderSource = vsSource.c_str();

	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(m_vertexShader);

	// FRAGMENT SHADER
	std::string fsSource = readFile(fsPath);
	const char* fragmentShaderSource = fsSource.c_str();

	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(m_fragmentShader);

	// SHADER PROGRAM
	m_program = glCreateProgram();
	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);

	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(m_program);
}

void Shader::useProgram() {
	glUseProgram(m_program);
}

