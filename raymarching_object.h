#ifndef	_RAYMARCHINNG_OBJECT_H_
#define	_RAYMARCHINNG_OBJECT_H_

#include <cmath>

#include "vec.h"
#include "ray.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"

namespace edupt {

struct RaymarchingObject {
	static const int kREP = 64;

	Color emission;
	Color color;
	ReflectionType reflection_type;

	RaymarchingObject(const Color &emission, const Color &color, const ReflectionType reflection_type) :
	  emission(emission), color(color), reflection_type(reflection_type) {}

	float distanceFunction(const Vec &position) const {
		return (position - Vec(65, 20, 20)).length() - 15.0;
	}

	Vec calcNormal(const Vec &position) const {
		return normalize(Vec(
			distanceFunction(position + Vec( kEPS, 0.0, 0.0 ) ) - distanceFunction(position + Vec( -kEPS, 0.0, 0.0 ) ),
			distanceFunction(position + Vec( 0.0, kEPS, 0.0 ) ) - distanceFunction(position + Vec( 0.0, -kEPS, 0.0 ) ),
			distanceFunction(position + Vec( 0.0, 0.0, kEPS ) ) - distanceFunction(position + Vec( 0.0, 0.0, -kEPS ) )
		));
	}

	// 入力のrayに対する交差点までの距離を返す。交差しなかったら0を返す。
	// rayとの交差判定を行う。交差したらtrue,さもなくばfalseを返す。
	bool intersect(const Ray &ray, Hitpoint *hitpoint) const {
		float dist;
		float depth = 0.0;
		Vec p = ray.org;
		for (int i = 0; i < kREP; i++) {
			dist = distanceFunction(p);
			depth += dist;
			p = ray.org + depth * ray.dir;
			if (abs(dist) < kEPS) break;
		}

		if (abs(dist) < kEPS) {
			hitpoint->position = p;
			hitpoint->normal = calcNormal(p);
			return true;
		} else {
			return false;
		}
	}
};

};

#endif
