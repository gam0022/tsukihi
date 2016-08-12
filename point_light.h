#ifndef	_POINT_LIGHT_H_
#define	_POINT_LIGHT_H_

#include <cmath>

#include "vec3.h"
#include "ray.h"
#include "material.h"
#include "object.h"

namespace edupt {

	struct PointLight : public Sphere {
	public:
		PointLight(const double radius, const Vec3 &position, const Color &emission) :
			Sphere(radius, position, emission, Vec3(), REFLECTION_TYPE_FAKE) {}
	};

};

#endif
