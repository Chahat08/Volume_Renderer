#include "GLFWInput.h"

GLFWInput::GLFWInput(GLFWwindow* window) :m_window(window) {}

void GLFWInput::processInput() {
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}
}