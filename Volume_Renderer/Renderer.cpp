#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Renderer::Renderer(){}

void Renderer::processFrame() {
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::setClearColor(float r, float g, float b) {
	clearColor = glm::vec3(r, g, b);
}