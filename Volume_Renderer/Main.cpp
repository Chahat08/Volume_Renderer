#include <iostream>
#include "App.h"

int main(int argc, char* argv[]) {
	
	// command line args
	int windowWidth, windowHeight;
	std::string dataPath;
	bool isStereo;

	if (argc < 5) {
		// default arguments
		windowWidth = 800;
		windowHeight = 600;
		dataPath = "data/CTHead";
		isStereo = false;
	}
	else {
		windowWidth = int(argv[1]);
		windowHeight = int(argv[2]);
		dataPath = argv[3];
		isStereo = bool(argv[4]);
	}

	App application(windowWidth, windowHeight, dataPath, isStereo);
	application.run();

	return 0;
}