#include "App.h"
#include <iostream>
#include <chrono>

App::App(int width, int height, std::string dataPath, bool isStereo, std::string vsPath, std::string fsPath) {
	m_windowWidth = width;
	m_windowHeight = height;
	m_dataPath = dataPath;
	m_isStereo = isStereo;
	m_vertexShaderPath = vsPath;
	m_fragmentShaderPath = fsPath;
	if (!setup())
		std::cerr << "Application setup failed" << std::endl;
}

App::~App() {
	delete m_input;
	delete m_renderer;
	delete m_shader;
	delete m_camera;
	delete m_model;
	glfwTerminate();
}

bool App::setup() {
	//GLFW INITIALIZATION
	if (!glfwInit()) return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_STEREO, m_isStereo);

	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "Renderer", NULL, NULL);

	if (!m_window) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	// GLAD INITIALIZATION
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return false;

	m_camera = new Camera();
	m_shader = new Shader(m_vertexShaderPath, m_fragmentShaderPath);
	m_input = new GLFWInput(m_window, m_camera,m_model);
	m_model = new Model(m_dataPath);
	m_renderer = new Renderer(m_shader, m_camera, m_model);

	sceneSetup();

	return true;
}

void App::sceneSetup() {
	m_renderer->setClearColor(0.11, 0.004, 0.106);
}

void App::run() {
	std::chrono::steady_clock::time_point begin, end = std::chrono::steady_clock::now();
	while (!glfwWindowShouldClose(m_window)) {
		begin = end;
		m_input->processInput();
		m_renderer->processFrame();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
		
		end = std::chrono::steady_clock::now();
		m_camera->deltaTime = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 100000.0;
		m_model->deltaTime = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 100000.0;
	}
}