#include "Model.h"
#include <fstream>
#include <vector>
#include <cstdint>
#include <algorithm>

Model::Model(const std::string& dataPath) :m_dataPath(dataPath){
	deltaTime = 1.0f;
	m_modelMatrix = glm::mat4(1.0f);
	m_rotateSpeed = 0.0005f;
	m_filePrefix = "/CTHead.";
	m_numSlices = 113;

	setupBuffers();
}

unsigned char* Model::readTextureSlice(const std::string& filename, VolumeDataFormat fileFormat, int width, int height) {
	std::ifstream file(filename, std::ios::binary);

	if (fileFormat == STANFORD) {

		std::vector<int16_t> slice(width * height);
		file.read(reinterpret_cast<char*>(slice.data()), slice.size() * sizeof(int16_t));

		unsigned char* sliceConverted = new unsigned char[width * height];
		for (size_t i = 0; i < slice.size(); ++i) {
			uint16_t temp = static_cast<uint16_t>(slice[i]);
			temp = (temp >> 8) | (temp << 8); // Convert to host byte order
			sliceConverted[i] = static_cast<unsigned char>(temp / 256); // Scale down to 8-bit
		}

		return sliceConverted;
	}

	return nullptr;
}

void Model::initialize3DTexture() {
	int width = 256;
	int height = 256;
	int depth = m_numSlices;

	unsigned char* volumeData = new unsigned char[width * height * depth];

	for (int i = 0; i < m_numSlices; ++i) {
		std::string file = m_dataPath + m_filePrefix + std::to_string(i + 1);
		unsigned char* sliceData = readTextureSlice(file, STANFORD, 256, 256);

		for (int j = 0; j < width * height; ++j)
			volumeData[(i * width * height + j)] = sliceData[j];

		delete[] sliceData;
	}

	glGenTextures(1, &m_texture3D);
	glBindTexture(GL_TEXTURE_3D, m_texture3D);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, width, height, depth, 0, GL_RED, GL_UNSIGNED_BYTE, volumeData);

	glBindTexture(GL_TEXTURE_3D, 0);

	delete[] volumeData;
}

void Model::generateVertexData() {
	float zMin = -0.5, zMax = 0.5;

	float zStep = m_numSlices>1 ? (zMax - zMin) / (m_numSlices - 1) : 0;

	for (int i = 0; i < m_numSlices; ++i) {
		float zPos = zMin + i * zStep;
		float texCoordZ = (float)i / (m_numSlices - 1);

		m_vertexData.insert(m_vertexData.end(), {
			-0.5f,  0.5f, zPos,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, texCoordZ,
			 0.5f,  0.5f, zPos,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, texCoordZ,
			-0.5f, -0.5f, zPos,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, texCoordZ,
			  
			-0.5f, -0.5f, zPos,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, texCoordZ,
			 0.5f, -0.5f, zPos,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, texCoordZ,
			 0.5f,  0.5f, zPos,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, texCoordZ
		});
	}
}


void Model::setupBuffers() {
	initialize3DTexture();
	generateVertexData();

	m_numTriangles = m_numSlices * 2;

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size()*sizeof(GLfloat), m_vertexData.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//glBindVertexArray(0);
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

GLuint Model::get3DTexture() {
	return m_texture3D;
}