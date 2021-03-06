﻿#define _CRT_SECURE_NO_DEPRECATE
//#define _OMP_
#define _OPEN_GL_

#include <iostream>
#include <time.h>

#include "renderer/pathtracing_renderer.h"
#include "renderer/tsukihi_renderer.h"

int main(int argc, char **argv) {
#ifndef EMSCRIPTEN
	FILE *stream;
	stream = freopen("output.txt", "w", stdout);
#endif

	std::cout << "Raytracing and Raymarching hybrid 'fake' renderer: tsukihi" << std::endl << std::endl;
	clock_t start = clock();

	int s = 1;
	tsukihi::Renderer* renderer = new tsukihi::TsukihiRenderer();
	//renderer->render(640 * s / 4, 480 * s / 4, 1, s);
	renderer->render(256, 256, 1, s);

	//tsukihi::Renderer* renderer = new tsukihi::PathtracingRenderer();
	//renderer->render(640 /2 , 480 / 2, 5, s);

	delete renderer;

	clock_t end = clock();
	std::cout << "Total time: " << (double)(end - start) / CLOCKS_PER_SEC << "sec." << std::endl;

#ifndef EMSCRIPTEN
	fclose(stream);
#endif
}
