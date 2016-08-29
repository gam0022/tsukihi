#ifndef	_RAYMARCHINNG_OBJECT_H_
#define	_RAYMARCHINNG_OBJECT_H_

#include <cmath>

#include "vec3.h"
#include "ray.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "object/object.h"

namespace tsukihi {
	typedef double(*DistanceFunctionPtr)(const Vec3& p);

	struct RaymarchingObject : public Object {
	public:
		int kREP = 256;
		double kREPS = 1e-4;

		Vec3 position = Vec3(0.0, 0.0, 0.0);
		double scale = 1.0;

		RaymarchingObject(const Vec3 &position, const double scale, const Color &emission, const Color &color, const ReflectionType reflection_type) :
			position(position), scale(scale), Object(emission, color, reflection_type) {
		}

		Vec3 calcNormal(const Vec3 &p) const;
		bool intersect(const Ray &ray, Hitpoint *hitpoint) const;
		double RaymarchingObject::transform(const Vec3 &p, DistanceFunctionPtr f) const;
	};

	Vec3 RaymarchingObject::calcNormal(const Vec3 &p) const {
		return normalize(Vec3(
			distanceFunction(p + Vec3(kEPS, 0.0, 0.0)) - distanceFunction(p + Vec3(-kEPS, 0.0, 0.0)),
			distanceFunction(p + Vec3(0.0, kEPS, 0.0)) - distanceFunction(p + Vec3(0.0, -kEPS, 0.0)),
			distanceFunction(p + Vec3(0.0, 0.0, kEPS)) - distanceFunction(p + Vec3(0.0, 0.0, -kEPS))
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
			if (std::abs(d) < kREPS) break;
		}

		if (std::abs(d) < kREPS) {
			hitpoint->normal = calcNormal(p);
			hitpoint->position = p + hitpoint->normal * kREPS * 50;
			hitpoint->distance = distance;
			return true;
		}
		else {
			return false;
		}
	}

	double RaymarchingObject::transform(const Vec3 &p, DistanceFunctionPtr f) const {
		return f((p - position) / scale) * scale;
	}

};

#endif
