#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <time.h>

#include "render.h"

int main(int argc, char **argv) {
	std::cout << "Path tracing renderer: edupt" << std::endl << std::endl;
	clock_t start = clock();

	// 640x480の画像、(2x2) * 4 sample / pixel
	//edupt::render(640 / 1, 480 / 1, 1000, 1);
	edupt::render(640 / 1, 480 / 1, 1, 1);

	clock_t end = clock();
	std::cout << "Total time: " << (double)(end - start) / CLOCKS_PER_SEC << "sec." << std::endl;
}
