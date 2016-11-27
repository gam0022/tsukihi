#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>

#ifdef _OMP_
#include <omp.h>
#endif

#include "image.h"
#include "math/random.h"

namespace tsukihi {
	class Renderer {
	public:
		Renderer() {}
		int progressImageInterval;
		int render(const int width, const int height, int samples, const int supersamples);
		virtual Color radiance(const Ray &ray, Random *rnd, const int depth) { return Color(); }

	private:
		int progres_image_count = 0;
		inline bool saveProgressImage(Color *image, int width, int height, int y);
	};

	inline bool Renderer::saveProgressImage(Color *image, int width, int height, int y) {
		if (y % progressImageInterval != 0) return false;

		char buffer[100];
		snprintf(buffer, 100, "%03d.png", progres_image_count);
		std::string filename(buffer);
		save_png_file(filename, image, width, height);
		++progres_image_count;
		return true;
	}

	int Renderer::render(const int width, const int height, int samples, const int supersamples) {
		progressImageInterval = height / 6;

		setup();

		// ワールド座標系でのスクリーンの大きさ
		const double screen_width = 30.0 * width / height;
		const double screen_height = 30.0;
		// スクリーンまでの距離
		const double screen_dist = 40.0;// *0.3;
		// スクリーンを張るベクトル
		const Vec3 screen_x = normalize(cross(camera_dir, camera_up)) * screen_width;
		const Vec3 screen_y = normalize(cross(screen_x, camera_dir)) * screen_height;
		const Vec3 screen_center = camera_position + camera_dir * screen_dist;

		Color *image = new Color[width * height];

		std::cout << width << "x" << height << " " << samples * (supersamples * supersamples) << " spp" << std::endl;

		// OpenMP
#pragma omp parallel for schedule(dynamic, 1)// num_threads(8)
		for (int y = 0; y < height; y++) {
#ifdef _OMP_
			if (y == 0) {
				std::cout << "threads: " << omp_get_num_threads() << std::endl;
			}
#endif
			std::cerr << "Rendering (y = " << y << ") " << (100.0 * y / (height - 1)) << "%" << std::endl;

			saveProgressImage(image, width, height, y);

			Random rnd(y + 1);
			for (int x = 0; x < width; x++) {
				const int image_index = (height - y - 1) * width + x;
				// supersamples x supersamples のスーパーサンプリング
				for (int sy = 0; sy < supersamples; sy++) {
					for (int sx = 0; sx < supersamples; sx++) {
						Color accumulated_radiance = Color();
						// 一つのサブピクセルあたりsamples回サンプリングする
						for (int s = 0; s < samples; s++) {
							const double rate = (1.0 / supersamples);
							const double r1 = sx * rate + rate / 2.0;
							const double r2 = sy * rate + rate / 2.0;
							// スクリーン上の位置
							const Vec3 screen_position =
								screen_center +
								screen_x * ((r1 + x) / width - 0.5) +
								screen_y * ((r2 + y) / height - 0.5);
							// レイを飛ばす方向
							const Vec3 dir = normalize(screen_position - camera_position);
							accumulated_radiance += radiance(Ray(camera_position, dir), &rnd, 0) / samples / (supersamples * supersamples);
						}
						image[image_index] = image[image_index] + accumulated_radiance;
					}
				}
			}
		}

		// 出力
		//hdr_correction(image, width, height);
		save_png_file(std::string("image.png"), image, width, height);
		//save_ppm_file(std::string("image.ppm"), image, width, height);
		return 0;
	}
};

#endif
