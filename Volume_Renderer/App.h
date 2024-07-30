#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLFWInput.h"
#include "Renderer.h"

class App {
public:
	App(int height, int width, std::string dataPath, bool isStereo, std::string vertexShaderPath, std::string fragmentShaderPath);
	~App();

	void run();

private:
	std::string m_dataPath;
	int m_windowWidth, m_windowHeight;
	bool m_isStereo;
	std::string m_vertexShaderPath, m_fragmentShaderPath;

	GLFWwindow* m_window;
	GLFWInput* m_input;
	Camera* m_camera;
	Model* m_model;
	Shader* m_shader;
	Renderer* m_renderer;

	bool setup();
};