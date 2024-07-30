#include "Model.h"
#include <fstream>
#include <vector>
#include <cstdint>
#include <algorithm>

unsigned char* readSlice(const std::string& filename, int width, int height) {
	std::ifstream file(filename, std::ios::binary);

	// Allocate memory for the slice
	std::vector<int16_t> slice(width * height);
	file.read(reinterpret_cast<char*>(slice.data()), slice.size() * sizeof(int16_t));

	// Convert from big-endian to host byte order and then to unsigned char
	unsigned char* slice8 = new unsigned char[256 * 256];
	for (size_t i = 0; i < slice.size(); ++i) {
		uint16_t temp = static_cast<uint16_t>(slice[i]);
		temp = (temp >> 8) | (temp << 8); // Convert to host byte order
		slice8[i] = static_cast<unsigned char>(temp / 256); // Scale down to 8-bit
	}

	return slice8;
}

Model::Model(const std::string& dataPath) :m_dataPath(dataPath){
	vertexDataSetup();

	deltaTime = 1.0f;
	m_modelMatrix = glm::mat4(1.0f);
	m_rotateSpeed = 0.0005f;
}

void Model::vertexDataSetup() {

	//int width = 256, height = 256;
	//unsigned char* data = readSlice("data/CThead/CThead.50", width, height);

	//unsigned int texture;
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//// set the texture wrapping/filtering options (on the currently bound texture object)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
	//glGenerateMipmap(GL_TEXTURE_2D);

	std::vector<GLfloat> vertexVals = { -0.5,  0.5, 0.0,	1.0,0.0,0.0,
										 0.5,  0.5, 0.0,	0.0,1.0,0.0,
									    -0.5, -0.5, 0.0,	0.0,0.0,1.0, 
										-0.5, -0.5, 0.0,	0.0,0.0,1.0,
										 0.5, -0.5, 0.0,    0.0,0.0,1.0,
										 0.5,  0.5, 0.0,	0.0,1.0,0.0,
	};

	m_numTriangles = 2;

	/*std::vector<GLfloat> vertexVals = { 0.1, 0.8,0.0,	1.0,0.0,0.0,
										0.7,-0.2,0.0,	0.0,1.0,0.0,
									   -0.7,-0.2,0.0,	0.0,0.0,1.0, };*/

	for (int i = 0; i < vertexVals.size(); ++i)
		m_vertexData[i] = vertexVals[i];

	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexData), m_vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

void Model::rotate(const glm::vec3& axis, float angle) {
	m_modelMatrix = glm::rotate(m_modelMatrix, angle * deltaTime * m_rotateSpeed, axis);
}

void Model::scaleUniform(float factor) {
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(factor * deltaTime));
}

glm::mat4 Model::getModelMatrix() {
	return m_modelMatrix;
}

GLuint Model::getVertexArray() {
	return m_vao;
}

int Model::getNumTriangles() {
	return m_numTriangles;
}