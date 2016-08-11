#ifndef _PPM_H_
#define _PPM_H_

#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "material.h"

namespace edupt {

inline double clamp(double x){ 
	if (x < 0.0)
		return 0.0;
	if (x > 1.0)
		return 1.0;
	return x;
} 

inline int to_int(double x){
	return int(pow(clamp(x), 1/2.2) * 255 + 0.5);
}

void save_ppm_file(const std::string &filename, const Color *image, const int width, const int height) {
	FILE *f = fopen(filename.c_str(), "wb");
	fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
	for (int i = 0; i < width * height; i++)
		fprintf(f,"%d %d %d ", to_int(image[i].x), to_int(image[i].y), to_int(image[i].z));
	fclose(f);
}

void save_png_file(const std::string &filename, const Color *image, const int width, const int height) {
	int bpp = 3;
	unsigned char* pixels = new unsigned char[width * height * bpp];
	for (int i = 0; i < width * height; i++) {
		pixels[i * 3]     = to_int(image[i].x);
		pixels[i * 3 + 1] = to_int(image[i].y);
		pixels[i * 3 + 2] = to_int(image[i].z);
	}
	stbi_write_png(filename.c_str(), width, height, bpp, pixels, width * bpp);
	delete pixels;
}

};

#endif
