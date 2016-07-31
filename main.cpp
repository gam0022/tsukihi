#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

#include "render.h"

int main(int argc, char **argv) {
	std::cout << "Path tracing renderer: edupt" << std::endl << std::endl;

	// 640x480の画像、(2x2) * 4 sample / pixel
	edupt::render(640 / 5, 480 / 5, 400, 1);
}
