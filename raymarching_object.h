#ifndef	_RAYMARCHINNG_OBJECT_H_
#define	_RAYMARCHINNG_OBJECT_H_

#include <cmath>

#include "vec3.h"
#include "ray.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "object.h"

namespace tukihi {

struct RaymarchingObject : public Object {
public:
	static const int kREP = 64;

	RaymarchingObject(const Color &emission, const Color &color, const ReflectionType reflection_type) : Object(emission, color, reflection_type) {
	}

	Vec3 calcNormal(const Vec3 &position) const;
	bool intersect(const Ray &ray, Hitpoint *hitpoint) const;
};

Vec3 RaymarchingObject::calcNormal(const Vec3 &position) const {
	return normalize(Vec3(
		distanceFunction(position + Vec3(kEPS, 0.0, 0.0)) - distanceFunction(position + Vec3(-kEPS, 0.0, 0.0)),
		distanceFunction(position + Vec3(0.0, kEPS, 0.0)) - distanceFunction(position + Vec3(0.0, -kEPS, 0.0)),
		distanceFunction(position + Vec3(0.0, 0.0, kEPS)) - distanceFunction(position + Vec3(0.0, 0.0, -kEPS))
	));
}

bool RaymarchingObject::intersect(const Ray &ray, Hitpoint *hitpoint) const {
	double d;
	double distance = 0.0;
	Vec3 p = ray.org;
	for (int i = 0; i < kREP; i++) {
		d = distanceFunction(p);
		distance += d;
		p = ray.org + distance * ray.dir;
		if (std::abs(d) < kEPS) break;
	}

	if (std::abs(d) < kEPS) {
		hitpoint->normal = calcNormal(p);
		hitpoint->position = p + hitpoint->normal * kEPS * 100;
		hitpoint->distance = distance;
		return true;
	} else {
		return false;
	}
}

};

#endif
