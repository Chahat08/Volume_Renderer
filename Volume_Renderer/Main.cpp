#include <iostream>
#include "App.h"

int main(int argc, char* argv[]) {
	
	// command line args
	int windowWidth, windowHeight;
	std::string dataPath;
	bool isStereo;
	std::string vertexShaderPath, fragmentShaderPath;

	if (argc < 7) {
		// default arguments
		windowWidth = 800;
		windowHeight = 800;
		dataPath = "data/MRBrain";
		isStereo = false;
		vertexShaderPath = "shaders/VertexShaderSource.vert";
		fragmentShaderPath = "shaders/FragmentShaderSource.frag";
	}
	else {
		windowWidth = int(argv[1]);
		windowHeight = int(argv[2]);
		dataPath = argv[3];
		isStereo = bool(argv[4]);
		vertexShaderPath = argv[5];
		fragmentShaderPath = argv[6];
	}

	App application(windowWidth, windowHeight, dataPath, isStereo, vertexShaderPath, fragmentShaderPath);
	application.run();

	return 0;
}