#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

class Model {
public:
	Model(const std::string& dataPath);

	void rotate(const glm::vec3& axis, float angle);
	void scaleUniform(float factor);

	float deltaTime;

	glm::mat4 getModelMatrix();
	GLuint getVertexArray();
	int getNumTriangles();
	GLuint get3DTexture();

	enum VolumeDataFormat {
		STANFORD
	};

private:
	float m_rotateSpeed;

	glm::mat4 m_modelMatrix;

	std::string m_dataPath;
	std::string m_filePrefix;
	int m_numSlices;
	GLuint m_texture3D;

	std::vector<GLfloat> m_vertexData;
	GLuint m_vbo, m_vao;
	int m_numTriangles;

	unsigned char* readTextureSlice(const std::string& filename, VolumeDataFormat fileFormat = STANFORD, int width = 256, int height = 256);
	void initialize3DTexture();
	void generateVertexData();
	void setupBuffers();
};