#include "GLFWInput.h"
#include <iostream>

GLFWwindow* GLFWInput::m_window = nullptr;
Camera* GLFWInput::m_camera = nullptr;
Model* GLFWInput::m_model = nullptr;
double GLFWInput::m_cursor_xpos = 0.0;
double GLFWInput::m_cursor_ypos = 0.0;
double GLFWInput::m_init_xpos = 0.0;
double GLFWInput::m_init_ypos = 0.0;
bool GLFWInput::m_modelRotate = false;

//void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
//	GLFWInput::m_cursor_xpos = xpos;
//	GLFWInput::m_cursor_ypos = ypos;
//	//glfwGetCursorPos(GLFWInput::m_window, &GLFWInput::m_cursor_xpos, &GLFWInput::m_cursor_ypos);
//}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	// MODEL ROTATION
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			GLFWInput::m_init_xpos = GLFWInput::m_cursor_xpos;
			GLFWInput::m_init_ypos = GLFWInput::m_cursor_ypos;

			GLFWInput::m_modelRotate = true;
		}
		else {
			GLFWInput::m_modelRotate = false;
		}
	}

}

GLFWInput::GLFWInput(GLFWwindow* window, Camera* camera, Model* model) {
	m_window = window;
	m_camera = camera;
	m_model = model;
	// glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
}

void GLFWInput::processInput() {
	// WINDOW CLOSE
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}

	// CAMERA MOVEMENTS
	// translation
	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
		m_camera->move(m_camera->MOVE_FORWARD);
	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		m_camera->move(m_camera->MOVE_BACKWARD);
	if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		m_camera->move(m_camera->MOVE_LEFT);
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		m_camera->move(m_camera->MOVE_RIGHT);
	if (glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS)
		m_camera->move(m_camera->MOVE_UPWARD);
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		m_camera->move(m_camera->MOVE_DOWNWARD);

	// changing look at


	// MODEL TRANSFORMATIONS
	// rotation
	glfwGetCursorPos(m_window, &m_cursor_xpos, &m_cursor_ypos);

	if (m_modelRotate) {
		glm::vec2 initCursorPos(m_init_xpos, m_init_ypos);
		glm::vec2 currCursorPos(m_cursor_xpos, m_cursor_ypos);
		glm::vec2 cursorMovementDir = currCursorPos - initCursorPos;

		float rotationAngleOffset = glm::length(cursorMovementDir);

		if (rotationAngleOffset > 0.0f) {
			glm::vec3 rotationAxis = glm::normalize(glm::vec3(cursorMovementDir.y, -cursorMovementDir.x, 0.0f));
			float angle = rotationAngleOffset;
			m_model->rotate(rotationAxis, angle);

			//m_init_xpos = m_cursor_xpos;
			//m_init_ypos = m_cursor_ypos;
		}
	}

}