#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <time.h>

#include "renderer.h"

int main(int argc, char **argv) {
	FILE *stream;
	freopen_s(&stream, "output.txt", "w", stdout);

	std::cout << "Raytracing and Raymarching hybrid 'fake' renderer: tukihi" << std::endl << std::endl;
	clock_t start = clock();

	auto renderer = new tukihi::Renderer();
	int s = 2;
	renderer->render(640 * s, 480 * s, tukihi::RENDER_MODE_FAKE, 1, s);
	delete renderer;

	clock_t end = clock();
	std::cout << "Total time: " << (double)(end - start) / CLOCKS_PER_SEC << "sec." << std::endl;
	fclose(stream);
}
