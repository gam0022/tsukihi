#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <time.h>

#include "pathtracing_renderer.h"
#include "tsukihi_renderer.h"

int main(int argc, char **argv) {
	FILE *stream;
	freopen_s(&stream, "output.txt", "w", stdout);

	std::cout << "Raytracing and Raymarching hybrid 'fake' renderer: tukihi" << std::endl << std::endl;
	clock_t start = clock();

	int s = 2;
    tukihi::Renderer* renderer = new tukihi::TsukihiRenderer();
	renderer->render(640 * s, 480 * s, 1, s);

	//tukihi::Renderer* renderer = new tukihi::PathtracingRenderer();
	//renderer->render(640 /2 , 480 / 2, 5, s);

	delete renderer;

	clock_t end = clock();
	std::cout << "Total time: " << (double)(end - start) / CLOCKS_PER_SEC << "sec." << std::endl;
	fclose(stream);
}
