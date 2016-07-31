#ifndef	_RAYMARCHINNG_OBJECT_H_
#define	_RAYMARCHINNG_OBJECT_H_

#include <cmath>

#include "vec.h"
#include "ray.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "object.h"

namespace edupt {

struct RaymarchingObject : public Object {
public:
	static const int kREP = 64;

	RaymarchingObject(const Color &emission, const Color &color, const ReflectionType reflection_type) : Object(emission, color, reflection_type) {
	}

	float distanceFunction(const Vec &position) const {
		return (position - Vec(65, 20, 20)).length() - 20.0;
	}

	Vec calcNormal(const Vec &position) const {
		return normalize(Vec(
			distanceFunction(position + Vec( kEPS, 0.0, 0.0 ) ) - distanceFunction(position + Vec( -kEPS, 0.0, 0.0 ) ),
			distanceFunction(position + Vec( 0.0, kEPS, 0.0 ) ) - distanceFunction(position + Vec( 0.0, -kEPS, 0.0 ) ),
			distanceFunction(position + Vec( 0.0, 0.0, kEPS ) ) - distanceFunction(position + Vec( 0.0, 0.0, -kEPS ) )
		));
	}

	bool intersect(const Ray &ray, Hitpoint *hitpoint) const;
};

bool RaymarchingObject::intersect(const Ray &ray, Hitpoint *hitpoint) const {
	//std:cout << "RaymarchingObject::intersect" << std::endl;

	float d;
	float distance = 0.0;
	Vec p = ray.org;
	for (int i = 0; i < kREP; i++) {
		d = distanceFunction(p);
		distance += d;
		p = ray.org + distance * ray.dir;
		if (abs(d) < kEPS) break;
	}

	if (abs(d) < kEPS) {
		hitpoint->position = p;
		hitpoint->normal = calcNormal(p);
		hitpoint->distance = distance;
		return true;
	} else {
		return false;
	}
}

};

#endif
