#ifndef	_SPHERE_H_
#define	_SPHERE_H_

#include <cmath>

#include "math/vec3.h"
#include "ray.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "object/object.h"

namespace tsukihi {

	struct Sphere : public Object {
	public:
		double radius;
		Vec3 position;

		Sphere(const double radius, const Vec3 &position, const Color &emission, const Color &color, const ReflectionType reflection_type) :
			radius(radius), position(position), Object(emission, color, reflection_type) {}

		bool intersect(const Ray &ray, Hitpoint *hitpoint) const;
		double distanceFunction(const Vec3& p) const;
	};

	bool Sphere::intersect(const Ray &ray, Hitpoint *hitpoint) const {
		const Vec3 p_o = position - ray.org;
		const double b = dot(p_o, ray.dir);
		const double D4 = b * b - dot(p_o, p_o) + radius * radius;

		if (D4 < 0.0)
			return false;

		const double sqrt_D4 = sqrt(D4);
		const double t1 = b - sqrt_D4, t2 = b + sqrt_D4;

		if (t1 < kEPS && t2 < kEPS)
			return false;

		if (t1 > kEPS) {
			hitpoint->distance = t1;
		}
		else {
			hitpoint->distance = t2;
		}

		hitpoint->position = ray.org + hitpoint->distance * ray.dir;
		hitpoint->normal = normalize(hitpoint->position - position);
		return true;
	}

	double Sphere::distanceFunction(const Vec3& p) const {
		return length(p - position) - radius;
	}

};

#endif
