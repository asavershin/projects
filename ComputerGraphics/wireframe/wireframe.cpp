#include <iostream>
#include <fstream>
#include "objFileProection.h"


int main(int argc, char** argv) {
	if (argc < 4) {
		return 1;
	}
	std::ifstream inFile(argv[3]);
	if (!inFile) {
		return 2;
	}
	try {

		int width = std::stoi(argv[1]);
		int height = std::stoi(argv[2]);

		objFileProection objFile(inFile);
		rgbImg objOXY(width, height);
		rgbImg objOYZ(width, height);
		rgbImg objOXZ(width, height);
	
		
		objFile.proectionsBMP(objOXY, objOXZ, objOYZ);

		objOXY.save((std::string(argv[3]) + ".Oxy.bmp").c_str());
		objOYZ.save((std::string(argv[3]) + ".Oxz.bmp").c_str());
		objOXZ.save((std::string(argv[3]) + ".Oyz.bmp").c_str());

		inFile.close();
	}
	catch (std::exception& e) {
		std::cout << "Error. " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error. " << std::endl;
	}
	return 0;
}
