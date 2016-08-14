#ifndef _FAKE_RADIANCE_H_
#define _FAKE_RADIANCE_H_

#include <algorithm>

#include "ray.h"
#include "scene.h"
#include "sphere.h"
#include "intersection.h"
#include "random.h"

namespace tukihi {
	const double shadowIntensity = 0.3;
	const double shadowSharpness = 8.0;

	inline double calcAO(Vec3 pos, Vec3 normal) {
		double sca = 1.5, occ = 0.0;
		for (int i = 0; i < 5; i++) {
			double hr = 0.01 + i / 8.0;
			double dd = map(normal * hr + pos);
			occ += (hr - dd) * sca;
			sca *= 0.7;
		}
		return clamp(1.0 - occ, 0.0, 1.0);
	}

	inline double calcSoftShadow(Vec3 ro, Vec3 rd) {
		double dist;
		double depth = 0.5;
		double bright = 1.0;
		for (int i = 0; i < 30; i++) {
			dist = map(ro + rd * depth);
			if (dist < kEPS) return shadowIntensity;
			bright = std::min(bright, shadowSharpness * dist / depth);
			depth += dist;
		}
		return shadowIntensity + (1.0 - shadowIntensity) * bright;
	}

	/*inline double softShadow(Vec3 ro, Vec3 lp, double k) {

	// More would be nicer. More is always nicer, but not really affordable... Not on my slow test machine, anyway.
	const int maxIterationsShad = 16;

	Vec3 rd = (lp - ro); // Unnormalized direction ray.

	double shade = 1.0;
	double dist = 0.05;
	double end = std::max(length(rd), 0.001);
	double stepDist = end / double(maxIterationsShad);

	rd /= end;

	// Max shadow iterations - More iterations make nicer shadows, but slow things down. Obviously, the lowest
	// number to give a decent shadow is the best one to choose.
	for (int i = 0; i<maxIterationsShad; i++) {

	double h = map(ro + rd * dist);
	//shade = min(shade, k*h/dist);
	shade = std::min(shade, smoothstep(0.0, 1.0, k * h / dist)); // Subtle difference. Thanks to IQ for this tidbit.
	//dist += min( h, stepDist ); // So many options here: dist += clamp( h, 0.0005, 0.2 ), etc.
	dist += clamp(h, 0.02, 0.25);

	// Early exits from accumulative distance function calls tend to be a good thing.
	if (h<0.001 || dist > end) break;
	}

	// I've added 0.5 to the final shade value, which lightens the shadow a bit. It's a preference thing.
	return std::min(std::max(shade, 0.0) + 0.25, 1.0);
	}*/

	// ray��������̕��ˋP�x�����߂�
	Color radiance_by_fake(const Ray &ray, Random *rnd, const int depth) {
		Intersection intersection;
		// �V�[���ƌ�������
		if (!intersect_scene(ray, &intersection))
			return kBackgroundColor;

		const Object* now_object = objects[intersection.object_id];
		const Hitpoint &hitpoint = intersection.hitpoint;
		const Vec3 orienting_normal = dot(hitpoint.normal, ray.dir) < 0.0 ? hitpoint.normal : (-1.0 * hitpoint.normal); // �����ʒu�̖@���i���̂���̃��C�̓��o���l���j
																														// �F�̔��˗��ő�̂��̂𓾂�B���V�A�����[���b�g�Ŏg���B
																														// ���V�A�����[���b�g��臒l�͔C�ӂ����F�̔��˗������g���Ƃ��ǂ��B
		double russian_roulette_probability = std::max(now_object->color.x, std::max(now_object->color.y, now_object->color.z));

		// ���ˉ񐔂����ȏ�ɂȂ����烍�V�A�����[���b�g�̊m�����}�㏸������B�i�X�^�b�N�I�[�o�[�t���[�΍�j
		if (depth > kDpethLimit)
			russian_roulette_probability *= pow(0.5, depth - kDpethLimit);

		// ���V�A�����[���b�g�����s���ǐՂ�ł��؂邩�ǂ����𔻒f����B
		// ������Depth��̒ǐՂ͕ۏႷ��B
		if (depth > kDepth) {
			if (rnd->next01() >= russian_roulette_probability)
				return now_object->emission;
		}
		else
			russian_roulette_probability = 1.0; // ���V�A�����[���b�g���s���Ȃ�����

		Color incoming_radiance;
		Color weight = 1.0;

		switch (now_object->reflection_type) {

			// ���S�g�U�˂ł͂Ȃ�
		case REFLECTION_TYPE_DIFFUSE: {
			incoming_radiance = Vec3(0, 0, 0);
			double ambient = calcAO(hitpoint.position, orienting_normal) + 0.5;
			double diffuse = 0.0;
			double specular = 0.0;

			for (auto light : lights) {
				Vec3 light_direction = light->position - hitpoint.position;
				double length_squared = light_direction.length_squared();

				light_direction = normalize(light_direction);
				incoming_radiance += light->emission * calcSoftShadow(hitpoint.position, light_direction) / length_squared;

				diffuse += std::max(dot(orienting_normal, light_direction), 0.0);
				specular += pow(clamp(dot(reflect(light_direction, orienting_normal), ray.dir), 0.0, 1.0), 10.0);
			}
			weight = (ambient + diffuse) * now_object->color + specular;
		} break;

			// ���S����
		case REFLECTION_TYPE_SPECULAR: {
			// ���S���ʂȂ̂Ń��C�̔��˕����͌���I�B
			// ���V�A�����[���b�g�̊m���ŏ��Z����̂͏�Ɠ����B
			incoming_radiance = radiance_by_fake(Ray(hitpoint.position, ray.dir - hitpoint.normal * 2.0 * dot(hitpoint.normal, ray.dir)), rnd, depth + 1);
			weight = now_object->color / russian_roulette_probability;
		} break;

			// ���ܗ�kIor�̃K���X
		case REFLECTION_TYPE_REFRACTION: {
			const Ray reflection_ray = Ray(hitpoint.position, ray.dir - hitpoint.normal * 2.0 * dot(hitpoint.normal, ray.dir));
			const bool into = dot(hitpoint.normal, orienting_normal) > 0.0; // ���C���I�u�W�F�N�g����o��̂��A����̂�

																			// Snell�̖@��
			const double nc = 1.0; // �^��̋��ܗ�
			const double nt = kIor; // �I�u�W�F�N�g�̋��ܗ�
			const double nnt = into ? nc / nt : nt / nc;
			const double ddn = dot(ray.dir, orienting_normal);
			const double cos2t = 1.0 - nnt * nnt * (1.0 - ddn * ddn);

			if (cos2t < 0.0) { // �S����
				incoming_radiance = radiance_by_fake(reflection_ray, rnd, depth + 1);
				weight = now_object->color / russian_roulette_probability;
				break;
			}
			// ���܂̕���
			const Ray refraction_ray = Ray(hitpoint.position,
				normalize(ray.dir * nnt - hitpoint.normal * (into ? 1.0 : -1.0) * (ddn * nnt + sqrt(cos2t))));

			// Schlick�ɂ��Fresnel�̔��ˌW���̋ߎ����g��
			const double a = nt - nc, b = nt + nc;
			const double R0 = (a * a) / (b * b);

			const double c = 1.0 - (into ? -ddn : dot(refraction_ray.dir, -1.0 * orienting_normal));
			const double Re = R0 + (1.0 - R0) * pow(c, 5.0); // ���˕����̌������˂���ray.dir�̕����ɉ^�Ԋ����B�����ɋ��ܕ����̌������˂�������ɉ^�Ԋ����B
			const double nnt2 = pow(into ? nc / nt : nt / nc, 2.0); // ���C�̉^�ԕ��ˋP�x�͋��ܗ��̈قȂ镨�̊Ԃ��ړ�����Ƃ��A���ܗ��̔�̓��̕������ω�����B
			const double Tr = (1.0 - Re) * nnt2; // ���ܕ����̌������܂���ray.dir�̕����ɉ^�Ԋ���

												 // ���ȏヌ�C��ǐՂ�������܂Ɣ��˂̂ǂ��炩�����ǐՂ���B�i�����Ȃ��Ǝw���I�Ƀ��C��������j
												 // ���V�A�����[���b�g�Ō��肷��B
			const double probability = 0.25 + 0.5 * Re;
			if (depth > 2) {
				if (rnd->next01() < probability) { // ����
					incoming_radiance = radiance_by_fake(reflection_ray, rnd, depth + 1) * Re;
					weight = now_object->color / (probability * russian_roulette_probability);
				}
				else { // ����
					incoming_radiance = radiance_by_fake(refraction_ray, rnd, depth + 1) * Tr;
					weight = now_object->color / ((1.0 - probability) * russian_roulette_probability);
				}
			}
			else { // ���܂Ɣ��˂̗�����ǐ�
				incoming_radiance =
					radiance_by_fake(reflection_ray, rnd, depth + 1) * Re +
					radiance_by_fake(refraction_ray, rnd, depth + 1) * Tr;
				weight = now_object->color / (russian_roulette_probability);
			}
		} break;

		}

		return now_object->emission + multiply(weight, incoming_radiance);
	}
};

#endif