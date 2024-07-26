#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLFWInput.h"
#include "Renderer.h"

class App {
public:
	App(int height, int width, std::string dataPath, bool isStereo);

	void run();

private:
	std::string m_dataPath;
	int m_windowWidth, m_windowHeight;
	bool m_isStereo;

	GLFWwindow* m_window;
	GLFWInput* m_input;
	Renderer* m_renderer;

	bool setup();
	void sceneSetup();
	void terminate();
};