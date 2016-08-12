#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <time.h>

#include "render.h"

int main(int argc, char **argv) {
	freopen("output.txt", "w", stdout);

	std::cout << "Fake raytracing and raymarching renderer: tukihi" << std::endl << std::endl;
	clock_t start = clock();

	// 640x480の画像、(2x2) * 4 sample / pixel
	tukihi::render(640, 480, 1, 2);

	clock_t end = clock();
	std::cout << "Total time: " << (double)(end - start) / CLOCKS_PER_SEC << "sec." << std::endl;
}
