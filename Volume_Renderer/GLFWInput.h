#pragma once
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Model.h"

class GLFWInput {
public:
	GLFWInput(GLFWwindow* window, Camera* camera, Model* model);

	void processInput();

private:
	static GLFWwindow* m_window;
	static Camera* m_camera;
	static Model* m_model;

	static double m_cursor_xpos, m_cursor_ypos;
	static double m_init_xpos, m_init_ypos;

	static bool m_modelRotate;

	// callbacks
	friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	
};