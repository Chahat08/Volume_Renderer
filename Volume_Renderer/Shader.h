#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();

	void useProgram();
	
	template<typename T>
	bool setUniform(const std::string& name, const T& value);
private:
	GLuint m_vertexShader, m_fragmentShader;
	GLuint m_program;
};

template<typename T>
bool Shader::setUniform(const std::string& name, const T& value) {
	GLuint location = glGetUniformLocation(m_program, name.c_str());
	if (location == -1) return false;

	if constexpr (std::is_same_v<T, GLfloat>)
		glUniform1f(location, value);
	else if constexpr (std::is_same_v<T, GLint> || std::is_same_v<T, GLboolean>)
		glUniform1i(location, value);
	else if constexpr (std::is_same_v<T, glm::vec2>)
		glUniform2fv(location, value);
	else if constexpr (std::is_same_v<T, glm::vec3>)
		glUniform3fv(location, value);
	else if constexpr (std::is_same_v<T, glm::vec4>)
		glUniform4fv(location, value);
	else if constexpr (std::is_same_v<T, glm::mat4>)
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	else return false;

	return true;
}