#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "math.h"
#include "material.h"

namespace tsukihi {

	inline int to_int(double x) {
		return int(pow(clamp(x, 0.0, 1.0), 1 / 2.2) * 255 + 0.5);
	}

	void hdr_correction(Color *image, const int width, const int height) {
		double min = std::numeric_limits<double>::max();
		double max = std::numeric_limits<double>::min();

		for (int i = 0; i < width * height; i++) {
			min = std::min({ min, image[i].x, image[i].y, image[i].z });
			max = std::max({ max, image[i].x, image[i].y, image[i].z });
		}

		double w = max - min;
		for (int i = 0; i < width * height; i++) {
			image[i] = (image[i] - min) / w * 0.95 + 0.05;
		}
	}

	int save_ppm_file(const std::string &filename, const Color *image, const int width, const int height) {
		FILE *f;
		if (auto error = fopen_s(&f, filename.c_str(), "wb")) {
			return 0;
		}
		fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
		for (int i = 0; i < width * height; i++)
			fprintf(f, "%d %d %d ", to_int(image[i].x), to_int(image[i].y), to_int(image[i].z));
		fclose(f);
		return 1;
	}

	int save_png_file(const std::string &filename, const Color *image, const int width, const int height) {
		int bpp = 3;
		unsigned char* pixels = new unsigned char[width * height * bpp];
		for (int i = 0; i < width * height; i++) {
			pixels[i * 3] = to_int(image[i].x);
			pixels[i * 3 + 1] = to_int(image[i].y);
			pixels[i * 3 + 2] = to_int(image[i].z);
		}
		int ret = stbi_write_png(filename.c_str(), width, height, bpp, pixels, width * bpp);
		delete pixels;
		return ret;
	}

};

#endif
