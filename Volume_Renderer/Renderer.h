#pragma once
#include <glm/glm.hpp>

class Renderer {
public:
	Renderer();
	
	void processFrame();

	void setClearColor(float r, float g, float b);
private:
	glm::vec3 clearColor;

};