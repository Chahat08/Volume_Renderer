#pragma once
#include <GLFW/glfw3.h>

class GLFWInput {
public:
	GLFWInput(GLFWwindow* window);

	void processInput();

private:
	GLFWwindow* m_window;
};