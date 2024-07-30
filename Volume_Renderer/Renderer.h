#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "Shader.h"
#include "GLFWInput.h"
#include "Camera.h"
#include "Model.h"

class Renderer {
public:
	Renderer(Shader* shader, Camera* camera, Model* model);
	
	void processFrame();

	void setClearColor(float r, float g, float b);
private:
	glm::vec3 clearColor;
	float m_width = 800, m_height = 600;
	
	Shader* m_shader;
	Camera* m_camera;
	Model* m_model;

	glm::mat4 m_projection;
};